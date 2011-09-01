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
#include "flow.hh"

#include <string>
#include <ostream>
#include <stdexcept>

#include "netinet++/ethernet.hh"
#include "netinet++/ip.hh"

#include <netinet/in.h>

#include "vlog.hh"
#include "buffer.hh"
#include "openflow/openflow.h"
#include "packets.h"
#include "vlog.hh"
#include "openssl/md5.h"

#include <inttypes.h>
#include <netinet/in.h>
#include <string.h>
#include <config.h>
#include <sys/types.h>

namespace vigil {

static Vlog_module log("flow");

Flow::Flow() {
	init();
}

Flow::Flow(uint32_t in_port_, const Buffer& buffer) {
    size_t offset = 0;
    struct eth_header     *eth;
    struct snap_header    *eth_snap;
    struct vlan_header    *vlan;
    struct vlan_header    *vlan_last;
    struct mpls_header    *mpls;
    struct arp_eth_header *arp;
    struct ip_header      *ipv4;
    struct tcp_header     *tcp;
    struct udp_header     *udp;
    struct icmp_header    *icmp;
    struct sctp_header    *sctp;

	init();

	match.in_port = in_port_;

    /* Ethernet */

    if (buffer.size() < offset + sizeof(struct eth_header)) {
        return;
    }

    eth = (struct eth_header *)((uint8_t *)buffer.data() + offset);
    offset += sizeof(struct eth_header);

    if (ntohs(eth->eth_type) >= ETH_TYPE_II_START) {
        /* Ethernet II */
    	match.wildcards &= ~OFPFW_DL_TYPE;
    	memset(&match.dl_src_mask, 0x00, ETH_ADDR_LEN);
    	memset(&match.dl_dst_mask, 0x00, ETH_ADDR_LEN);

        memcpy(&match.dl_src, eth->eth_src, ETH_ADDR_LEN);
        memcpy(&match.dl_dst, eth->eth_dst, ETH_ADDR_LEN);
        match.dl_type = ntohs(eth->eth_type);

    } else {
        /* Ethernet 802.3 */
        struct llc_header *llc;

        // TODO Zoltan: compare packet length with ofpbuf length for validity

        if (buffer.size() < offset + sizeof(struct llc_header)) {
            return;
        }

        llc = (struct llc_header *)((uint8_t *)buffer.data() + offset);
        offset += sizeof(struct llc_header);

        if (!(llc->llc_dsap == LLC_DSAP_SNAP &&
              llc->llc_ssap == LLC_SSAP_SNAP &&
              llc->llc_cntl == LLC_CNTL_SNAP)) {
            return;
        }

        if (buffer.size() < offset + sizeof(struct snap_header)) {
            return;
        }

        eth_snap = (struct snap_header *)((uint8_t *)buffer.data() + offset);
        offset += sizeof(struct snap_header);

        if (memcmp(eth_snap->snap_org, SNAP_ORG_ETHERNET, sizeof(SNAP_ORG_ETHERNET)) != 0) {
            return;
        }

    	match.wildcards &= ~OFPFW_DL_TYPE;
    	memset(&match.dl_src_mask, 0x00, ETH_ADDR_LEN);
    	memset(&match.dl_dst_mask, 0x00, ETH_ADDR_LEN);

        memcpy(&match.dl_src, eth->eth_src, ETH_ADDR_LEN);
        memcpy(&match.dl_dst, eth->eth_dst, ETH_ADDR_LEN);
        match.dl_type = ntohs(eth_snap->snap_type);
    }

    /* VLAN */

    if (match.dl_type == ETH_TYPE_VLAN ||
    	match.dl_type == ETH_TYPE_VLAN_PBB) {

    	match.wildcards &= ~OFPFW_DL_VLAN;
    	match.wildcards &= ~OFPFW_DL_VLAN_PCP;

        if (buffer.size() < offset + sizeof(struct vlan_header)) {
            return;
        }
        vlan = (struct vlan_header *)((uint8_t *)buffer.data() + offset);
        vlan_last = vlan;
        offset += sizeof(struct vlan_header);

        match.dl_vlan = (ntohs(vlan->vlan_tci) & VLAN_VID_MASK) >> VLAN_VID_SHIFT;
        match.dl_vlan_pcp = (ntohs(vlan->vlan_tci) & VLAN_PCP_MASK) >> VLAN_PCP_SHIFT;
        // Note: DL type is updated
        match.dl_type = ntohs(vlan->vlan_next_type);
    } else {
        match.dl_vlan = OFPVID_NONE;
    }

    /* skip through rest of VLAN tags */
    while (match.dl_type == ETH_TYPE_VLAN ||
           match.dl_type == ETH_TYPE_VLAN_PBB) {

        if (buffer.size() < offset + sizeof(struct vlan_header)) {
            return;
        }
        vlan_last = (struct vlan_header *)((uint8_t *)buffer.data() + offset);
        offset += sizeof(struct vlan_header);

        match.dl_type = ntohs(vlan_last->vlan_next_type);
    }

    /* MPLS */

    if (match.dl_type == ETH_TYPE_MPLS ||
        match.dl_type == ETH_TYPE_MPLS_MCAST) {

        if (buffer.size() < offset + sizeof(struct mpls_header)) {
            return;
        }
        mpls = (struct mpls_header *)((uint8_t *)buffer.data() + offset);
        offset += sizeof(struct mpls_header);

    	match.wildcards &= ~OFPFW_MPLS_LABEL;
    	match.wildcards &= ~OFPFW_MPLS_TC;

        match.mpls_label = (ntohl(mpls->fields) & MPLS_LABEL_MASK) >> MPLS_LABEL_SHIFT;
        match.mpls_tc =    (ntohl(mpls->fields) & MPLS_TC_MASK) >> MPLS_TC_SHIFT;

        /* no processing past MPLS */
        return;
    }

    /* ARP */

    if (match.dl_type == ETH_TYPE_ARP) {
        if (buffer.size() < offset + sizeof(struct arp_eth_header)) {
            return;
        }
        arp = (struct arp_eth_header *)((uint8_t *)buffer.data() + offset);
        offset += sizeof(struct arp_eth_header);

        if (ntohs(arp->ar_hrd) == 1 &&
            ntohs(arp->ar_pro) == ETH_TYPE_IP &&
            arp->ar_hln == ETH_ADDR_LEN &&
            arp->ar_pln == 4) {

            if (ntohs(arp->ar_op) <= 0xff) {

            	match.wildcards &= ~OFPFW_NW_PROTO;

                match.nw_proto = ntohs(arp->ar_op);
            }
            if (match.nw_proto == ARP_OP_REQUEST ||
                match.nw_proto == ARP_OP_REPLY) {

            	match.nw_src_mask = 0x00000000;
            	match.nw_dst_mask = 0x00000000;

                match.nw_src = arp->ar_spa;
                match.nw_dst = arp->ar_tpa;
            }
        }

        return;
    }

    /* Network Layer */
    else if (match.dl_type == ETH_TYPE_IP) {
        if (buffer.size() < offset + sizeof(struct ip_header)) {
            return;
        }
        ipv4 = (struct ip_header *)((uint8_t *)buffer.data() + offset);
        offset += sizeof(struct ip_header);

    	match.wildcards &= ~OFPFW_NW_PROTO;
    	match.wildcards &= ~OFPFW_NW_TOS;
    	match.nw_src_mask = 0x00000000;
    	match.nw_dst_mask = 0x00000000;

        match.nw_src =   ipv4->ip_src;
        match.nw_dst =   ipv4->ip_dst;
        match.nw_tos =  (ipv4->ip_tos >> 2) & IP_DSCP_MASK;
        match.nw_proto = ipv4->ip_proto;

        if (IP_IS_FRAGMENT(ipv4->ip_frag_off)) {
            /* No further processing for fragmented IPv4 */
            return;
        }

        /* Transport */

        if (match.nw_proto == IP_TYPE_TCP) {
            if (buffer.size() < offset + sizeof(struct tcp_header)) {
                return;
            }
            tcp = (struct tcp_header *)((uint8_t *)buffer.data() + offset);
            offset += sizeof(struct tcp_header);

        	match.wildcards &= ~OFPFW_TP_SRC;
        	match.wildcards &= ~OFPFW_TP_DST;

            match.tp_src = ntohs(tcp->tcp_src);
            match.tp_dst = ntohs(tcp->tcp_dst);

            return;
        }

        else if (match.nw_proto == IP_TYPE_UDP) {
            if (buffer.size() < offset + sizeof(struct udp_header)) {
                return;
            }
            udp = (struct udp_header *)((uint8_t *)buffer.data() + offset);
            offset += sizeof(struct udp_header);

        	match.wildcards &= ~OFPFW_TP_SRC;
        	match.wildcards &= ~OFPFW_TP_DST;

            match.tp_src = ntohs(udp->udp_src);
            match.tp_dst = ntohs(udp->udp_dst);

            return;

        } else if (match.nw_proto == IP_TYPE_ICMP) {
            if (buffer.size() < offset + sizeof(struct icmp_header)) {
                return;
            }
            icmp = (struct icmp_header *)((uint8_t *)buffer.data() + offset);
            offset += sizeof(struct icmp_header);

        	match.wildcards &= ~OFPFW_TP_SRC;
        	match.wildcards &= ~OFPFW_TP_DST;

            match.tp_src = icmp->icmp_type;
            match.tp_dst = icmp->icmp_code;

            return;

        } else if (match.nw_proto == IP_TYPE_SCTP) {
            if (buffer.size() < offset + sizeof(struct sctp_header)) {
                return;
            }
            sctp = (struct sctp_header *)((uint8_t *)buffer.data() + offset);
            offset += sizeof(struct sctp_header);

        	match.wildcards &= ~OFPFW_TP_SRC;
        	match.wildcards &= ~OFPFW_TP_DST;

            match.tp_src = ntohs(sctp->sctp_src);
            match.tp_dst = ntohs(sctp->sctp_dst);

            return;
        }
    }
}
/** Constructor from ofp_match
 */

Flow::Flow(const struct ofl_match_standard *match_) {
	init();
	memcpy(&match, match_, sizeof(struct ofl_match_standard));
}

void
Flow::init() {
	  memset(&match, 0x00, sizeof(struct ofl_match_standard));
	  match.header.type = OFPMT_STANDARD;
	  match.wildcards   = OFPFW_ALL;
	  memset(&match.dl_src_mask, 0xff, ETH_ADDR_LEN);
	  memset(&match.dl_dst_mask, 0xff, ETH_ADDR_LEN);
	  match.nw_src_mask   = 0xffffffff;
	  match.nw_dst_mask   = 0xffffffff;
	  match.metadata_mask = 0xffffffffffffffffULL;
}

const std::string
Flow::to_string() const
{
	char *s = ofl_structs_match_to_string((struct ofl_match_header *)&match, NULL);
	const std::string ret(s);
	free(s);

	return ret;
}

std::ostream&
operator<<(std::ostream& stream, const Flow& f) 
{
    return stream << f.to_string();
}

uint64_t
Flow::hash_code() const
{
    unsigned char md[MD5_DIGEST_LENGTH];
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, &match, sizeof(struct ofl_match_standard));
    MD5_Final(md, &ctx);

    return *((uint64_t*)md);
}

bool operator==(const Flow& lhs, const Flow& rhs)
{
  return memcmp(&lhs.match, &rhs.match, sizeof(struct ofl_match_standard)) == 0;
}

bool operator!=(const Flow& lhs, const Flow& rhs)
{
  return !(lhs == rhs);
}

} // namespace vigil

