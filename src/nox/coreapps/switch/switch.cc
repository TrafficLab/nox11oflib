/* Copyright 2008 (C) Nicira, Inc.
 *
 * This file is part of NOX.
 *
 * NOX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NOX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NOX.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_array.hpp>
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <stdint.h>

#include "openflow-default.hh"
#include "assert.hh"
#include "component.hh"
#include "flow.hh"
#include "fnv_hash.hh"
#include "hash_set.hh"
#include "ofp-msg-event.hh"
#include "vlog.hh"

#include "netinet++/ethernetaddr.hh"
#include "netinet++/ethernet.hh"

#include "../../../oflib/ofl-actions.h"
#include "../../../oflib/ofl-messages.h"

using namespace vigil;
using namespace vigil::container;

namespace {

struct Mac_source
{
    /* Key. */
    datapathid datapath_id;     /* Switch. */
    ethernetaddr mac;           /* Source MAC. */

    /* Value. */
    mutable int port;           /* Port where packets from 'mac' were seen. */

    Mac_source() : port(-1) { }
    Mac_source(datapathid datapath_id_, ethernetaddr mac_)
        : datapath_id(datapath_id_), mac(mac_), port(-1)
        { }
};

bool operator==(const Mac_source& a, const Mac_source& b)
{
    return a.datapath_id == b.datapath_id && a.mac == b.mac;
}

bool operator!=(const Mac_source& a, const Mac_source& b) 
{
    return !(a == b);
}

struct Hash_mac_source
{
    std::size_t operator()(const Mac_source& val) const {
        uint32_t x;
        x = vigil::fnv_hash(&val.datapath_id, sizeof val.datapath_id);
        x = vigil::fnv_hash(val.mac.octet, sizeof val.mac.octet, x);
        return x;
    }
};

Vlog_module log("switch");

class Switch
    : public Component 
{
public:
    Switch(const Context* c,
           const json_object*) 
        : Component(c) { }

    void configure(const Configuration*);

    void install();

    Disposition handle(const Event&);

private:
    typedef hash_set<Mac_source, Hash_mac_source> Source_table;
    Source_table sources;

    /* Set up a flow when we know the destination of a packet?  This should
     * ordinarily be true; it is only usefully false for debugging purposes. */
    bool setup_flows;
};

void 
Switch::configure(const Configuration* conf) {
    setup_flows = true; // default value
    BOOST_FOREACH (const std::string& arg, conf->get_arguments()) {
        if (arg == "noflow") {
            setup_flows = false;
        } else {
            VLOG_WARN(log, "argument \"%s\" not supported", arg.c_str());
        }
    }
    
    register_handler(Ofp_msg_event::get_name(OFPT_PACKET_IN), boost::bind(&Switch::handle, this, _1));
}

void
Switch::install() {

}

Disposition
Switch::handle(const Event& e)
{
    const Ofp_msg_event& pi = assert_cast<const Ofp_msg_event&>(e);

    struct ofl_msg_packet_in *in = (struct ofl_msg_packet_in *)**pi.msg;
    Flow flow(in->in_port, (Nonowning_buffer(in->data, in->data_length)));

    /* drop all LLDP packets */
    if (flow.match.dl_type == ethernet::LLDP){
        return CONTINUE;
    }

    /* Learn the source. */
    ethernetaddr dl_src(flow.match.dl_src);
    if (!dl_src.is_multicast()) {
        Mac_source src(pi.dpid, dl_src);
        Source_table::iterator i = sources.insert(src).first;
        if (i->port != in->in_port) {
            i->port = in->in_port;
            VLOG_DBG(log, "learned that "EA_FMT" is on datapath %s port %d",
                     EA_ARGS(&dl_src), pi.dpid.string().c_str(),
                     (int) in->in_port);
        }
    } else {
        VLOG_DBG(log, "multicast packet source "EA_FMT, EA_ARGS(&dl_src));
    }

    /* Figure out the destination. */
    int out_port = -1;        /* Flood by default. */
    ethernetaddr dl_dst(flow.match.dl_dst);
    if (!dl_dst.is_multicast()) {
        Mac_source dst(pi.dpid, dl_dst);
        Source_table::iterator i(sources.find(dst));
        if (i != sources.end()) {
            out_port = i->port;
        }
    }

    /* Set up a flow if the output port is known. */
    if (setup_flows && out_port != -1) {

        struct ofl_action_output output =
                {{/*.type = */OFPAT_OUTPUT}, /*.port = */out_port, /*.max_len = */0};

        struct ofl_action_header *actions[] =
                { (struct ofl_action_header *)&output };

        struct ofl_instruction_actions apply =
        {{/*.type = */OFPIT_APPLY_ACTIONS}, /*.actions_num = */1, /*.actions = */actions};

        struct ofl_instruction_header *insts[] =
                { (struct ofl_instruction_header *)&apply };

        struct ofl_msg_flow_mod mod;
        mod.header.type = OFPT_FLOW_MOD;
        mod.cookie = 0x00ULL;
        mod.cookie_mask = 0x00ULL;
        mod.buffer_id = in->buffer_id;
        mod.table_id = 0; // use first table
        mod.command = OFPFC_ADD;
        mod.priority = OFP_DEFAULT_PRIORITY;
        mod.idle_timeout = 5;
        mod.hard_timeout = OFP_FLOW_PERMANENT;
        mod.flags = ofd_flow_mod_flags();
        mod.match = (struct ofl_match_header *)&flow.match;
        mod.instructions_num = 1;
        mod.instructions = insts;

        send_openflow_msg(pi.dpid, (struct ofl_msg_header *)&mod, 0/*xid*/, true/*block*/);
    }

    /* Send out packet if necessary. */
    if (!setup_flows || out_port == -1 || in->buffer_id == UINT32_MAX) {

        if (in->buffer_id == UINT32_MAX) {
            if (in->total_len != in->data_length) {
                /* Control path didn't buffer the packet and didn't send us
                 * the whole thing--what gives? */
                VLOG_DBG(log, "total_len=%"PRIu16" data_len=%zu\n",
                        in->total_len, in->data_length);
                return CONTINUE;
            }
            send_openflow_pkt(pi.dpid, Nonowning_buffer(in->data, in->data_length), in->in_port, out_port == -1 ? OFPP_FLOOD : out_port, true/*block*/);
        } else {
            send_openflow_pkt(pi.dpid, in->buffer_id, in->in_port, out_port == -1 ? OFPP_FLOOD : out_port, true/*block*/);
        }
    }
    return CONTINUE;
}

REGISTER_COMPONENT(container::Simple_component_factory<Switch>, Switch);

} // unnamed namespace
