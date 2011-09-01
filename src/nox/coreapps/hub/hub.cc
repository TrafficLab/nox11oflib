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
#include <boost/shared_array.hpp>
#include <netinet/in.h>
#include "assert.hh"
#include "component.hh"
#include "flow.hh"
//#include "packet-in.hh"
#include "ofp-msg-event.hh"
#include "vlog.hh"

#include "netinet++/ethernet.hh"

#include "../../../oflib/ofl-structs.h"
#include "../../../oflib/ofl-messages.h"

namespace {

using namespace vigil;
using namespace vigil::container;

Vlog_module lg("hub");

class Hub 
    : public Component 
{
public:
     Hub(const Context* c,
         const json_object*) 
         : Component(c) { }
    
    void configure(const Configuration*) {
    }

    Disposition handler(const Event& e)
    {
        const Ofp_msg_event& pi = assert_cast<const Ofp_msg_event&>(e);
        struct ofl_msg_packet_in *in = (struct ofl_msg_packet_in *)**pi.msg;

        Flow flow(in->in_port, (Array_buffer(in->data, in->data_length)));

        /* drop all LLDP packets */
        if (flow.match.dl_type == ethernet::LLDP){
            return CONTINUE;
        }

        struct ofl_action_output output =
                {{/*.type = */OFPAT_OUTPUT}, /*.port = */OFPP_FLOOD, /*.max_len = */0};

        struct ofl_action_header *actions[] =
                { (struct ofl_action_header *)&output };

        struct ofl_instruction_actions apply =
                {{/*.type = */OFPIT_APPLY_ACTIONS}, /*.actions_num = */1, /*.actions = */actions};

        struct ofl_instruction_header *insts[] =
                { (struct ofl_instruction_header *)&apply };

        struct ofl_msg_flow_mod mod =
                {{/*.type = */OFPT_FLOW_MOD},
                 /*.cookie = */0x00ULL,
                 /*.cookie_mask = */0x00ULL,
                 /*.table_id = */0,
                 /*.command = */OFPFC_ADD,
                 /*.idle_timeout = */5,
                 /*.hard_timeout = */5,
                 /*.priority = */OFP_DEFAULT_PRIORITY,
                 /*.buffer = */in->buffer_id,
                 /*.out_port = */OFPP_ANY,
                 /*.out_group = */OFPG_ANY,
                 /*.flags = */0x0000,
                 /*.match = */(struct ofl_match_header *)&flow.match,
                 /*.instructions_num = */1,
                 /*.instructions = */insts};

        send_openflow_msg(pi.dpid, (struct ofl_msg_header *)&mod, 0/*xid*/, true/*block*/);

        if (in->buffer_id == UINT32_MAX) {
            if (in->total_len == in->data_length) {
                send_openflow_pkt(pi.dpid, Array_buffer(in->data, in->data_length), in->in_port, OFPP_FLOOD, true/*block*/);
            } else {
                /* Control path didn't buffer the packet and didn't send us
                 * the whole thing--what gives? */
                lg.dbg("total_len=%zu data_len=%zu\n", in->total_len, in->data_length);
            }
        }

        return CONTINUE;
    }

    void install()
    {
        register_handler(Ofp_msg_event::get_name(OFPT_PACKET_IN), boost::bind(&Hub::handler, this, _1));
    }
};

REGISTER_COMPONENT(container::Simple_component_factory<Hub>, Hub);

} // unnamed namespace
