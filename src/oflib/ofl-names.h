/* Copyright (c) 2011, TrafficLab, Ericsson Research, Hungary
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the Ericsson Research nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Author: Zoltán Lajos Kis <zoltan.lajos.kis@ericsson.com>
 */

#ifndef OFL_NAMES_H
#define OFL_NAMES_H 1

#include "openflow/openflow.h"

struct ofl_names_8 {
    const uint8_t   code;
    const char     *name;
};

struct ofl_names_16 {
    const uint16_t   code;
    const char      *name;
};

struct ofl_names_32 {
    const uint32_t   code;
    const char      *name;
};

struct ofl_names_16_16 {
    const uint16_t   code1;
    const uint16_t   code2;
    const char      *name;
};



static struct ofl_names_32 ofl_port_names[] = {
        {OFPP_IN_PORT,    "in_port"},
        {OFPP_TABLE,      "table"},
        {OFPP_NORMAL,     "normal"},
        {OFPP_FLOOD,      "flood"},
        {OFPP_ALL,        "all"},
        {OFPP_CONTROLLER, "ctrl"},
        {OFPP_LOCAL,      "local"},
        {OFPP_ANY,        "any"}
};

static struct ofl_names_16 ofl_type_names[] = {
        {OFPT_HELLO,                    "hello"},
        {OFPT_ERROR,                    "error"},
        {OFPT_ECHO_REQUEST,             "echo_req"},
        {OFPT_ECHO_REPLY,               "echo_repl"},
        {OFPT_EXPERIMENTER,             "experim"},
        {OFPT_FEATURES_REQUEST,         "feat_req"},
        {OFPT_FEATURES_REPLY,           "feat_repl"},
        {OFPT_GET_CONFIG_REQUEST,       "conf_req"},
        {OFPT_GET_CONFIG_REPLY,         "conf_repl"},
        {OFPT_SET_CONFIG,               "set_conf"},
        {OFPT_PACKET_IN,                "pkt_in"},
        {OFPT_FLOW_REMOVED,             "flow_rem"},
        {OFPT_PORT_STATUS,              "port_stat"},
        {OFPT_PACKET_OUT,               "pkt_out"},
        {OFPT_FLOW_MOD,                 "flow_mod"},
        {OFPT_GROUP_MOD,                "grp_mod"},
        {OFPT_PORT_MOD,                 "port_mod"},
        {OFPT_TABLE_MOD,                "tab_mod"},
        {OFPT_STATS_REQUEST,            "stat_req"},
        {OFPT_STATS_REPLY,              "stat_repl"},
        {OFPT_BARRIER_REQUEST,          "barr_req"},
        {OFPT_BARRIER_REPLY,            "barr_repl"},
        {OFPT_QUEUE_GET_CONFIG_REQUEST, "q_cnf_req"},
        {OFPT_QUEUE_GET_CONFIG_REPLY,   "q_cnf_repl"}
};

static struct ofl_names_16 ofl_config_flag_names[] = {
        {OFPC_FRAG_NORMAL,               "frag_norm"},
        {OFPC_FRAG_DROP,                 "frag_drop"},
        {OFPC_FRAG_REASM,                "frag_reasm"},
        {OFPC_INVALID_TTL_TO_CONTROLLER, "inv_ttl"}
};

static struct ofl_names_32 ofl_table_config_names[] = {
        {OFPTC_TABLE_MISS_CONTROLLER, "to_ctrl"},
        {OFPTC_TABLE_MISS_CONTINUE,   "continue"},
        {OFPTC_TABLE_MISS_DROP,       "drop"}
};

static struct ofl_names_32 ofl_capabilities_names[] = {
        {OFPC_FLOW_STATS,   "flow_stats"},
        {OFPC_TABLE_STATS,  "table_stats"},
        {OFPC_PORT_STATS,   "port_stats"},
        {OFPC_GROUP_STATS,  "group_stats"},
        {OFPC_IP_REASM,     "ip_reasm"},
        {OFPC_QUEUE_STATS,  "queue_stats"},
        {OFPC_ARP_MATCH_IP, "arp_match"}
};

static struct ofl_names_32 ofl_port_config_names[] = {
        {OFPPC_PORT_DOWN,    "down"},
        {OFPPC_NO_RECV,      "drop"},
        {OFPPC_NO_FWD,       "no_fwd"},
        {OFPPC_NO_PACKET_IN, "no_pkt_in"}
};

static struct ofl_names_32 ofl_port_config_names[] = {
        {OFPPS_LINK_DOWN, "link_down"},
        {OFPPS_BLOCKED,   "blocked"},
        {OFPPS_LIVE,      "live"}
};

static struct ofl_names_32 ofl_port_features_names[] = {
        {OFPPF_10MB_HD,    "10MB_HD"},
        {OFPPF_10MB_FD,    "10MB_FD"},
        {OFPPF_100MB_HD,   "100MB_HD"},
        {OFPPF_100MB_FD,   "100MB_FD"},
        {OFPPF_1GB_HD,     "1GB_HD"},
        {OFPPF_1GB_FD,     "1GB_FD"},
        {OFPPF_10GB_FD,    "10GB_FD"},
        {OFPPF_40GB_FD,    "40GB_FD"},
        {OFPPF_100GB_FD,   "100GB_FD"},
        {OFPPF_1TB_FD,     "1TB_FD"},
        {OFPPF_OTHER,      "other_rate"},
        {OFPPF_COPPER,     "copper"},
        {OFPPF_FIBER,      "fiber"},
        {OFPPF_AUTONEG,    "auto-neg"},
        {OFPPF_PAUSE,      "pause"},
        {OFPPF_PAUSE_ASYM, "pause-asym"}
};

static struct ofl_names_8 ofl_port_reason_names[] = {
        {OFPPR_ADD,    "added"},
        {OFPPR_DELETE, "deleted"},
        {OFPPR_MODIFY, "modified"}
};

static struct ofl_names_8 ofl_packet_in_reason_names[] = {
        {OFPR_NO_MATCH, "no_match"},
        {OFPR_ACTION,   "action"}
};

static struct ofl_names_16 ofl_action_type_names[] = {
        {OFPAT_OUTPUT,         "output"},
        {OFPAT_SET_VLAN_VID,   "vlan_vid"},
        {OFPAT_SET_VLAN_PCP,   "vlan_pcp"},
        {OFPAT_SET_DL_SRC,     "dl_src"},
        {OFPAT_SET_DL_DST,     "dl_dst"},
        {OFPAT_SET_NW_SRC,     "nw_src"},
        {OFPAT_SET_NW_DST,     "nw_dst"},
        {OFPAT_SET_NW_TOS,     "nw_tos"},
        {OFPAT_SET_NW_ECN,     "nw_ecn"},
        {OFPAT_SET_TP_SRC,     "tp_src"},
        {OFPAT_SET_TP_DST,     "tp_dst"},
        {OFPAT_COPY_TTL_OUT,   "ttl_out"},
        {OFPAT_COPY_TTL_IN,    "ttl_in"},
        {OFPAT_SET_MPLS_LABEL, "mpls_label"},
        {OFPAT_SET_MPLS_TC,    "mpls_tc"},
        {OFPAT_SET_MPLS_TTL,   "mpls_ttl"},
        {OFPAT_DEC_MPLS_TTL,   "mpls_dec"},
        {OFPAT_PUSH_VLAN,      "push_vlan"},
        {OFPAT_POP_VLAN,       "pop_vlan"},
        {OFPAT_PUSH_MPLS,      "push_mpls"},
        {OFPAT_POP_MPLS,       "pop_mpls"},
        {OFPAT_SET_QUEUE,      "queue"},
        {OFPAT_GROUP,          "group"},
        {OFPAT_SET_NW_TTL,     "nw_ttl"},
        {OFPAT_DEC_NW_TTL,     "nw_dec"},
        {OFPAT_EXPERIMENTER,   "experim"}
};

static struct ofl_names_8 ofl_flow_mod_cmd_names[] = {
        {OFPFC_ADD,           "add"},
        {OFPFC_MODIFY,        "mod"},
        {OFPFC_MODIFY_STRICT, "mods"},
        {OFPFC_DELETE,        "del"},
        {OFPFC_DELETE_STRICT, "dels"}
};

static struct ofl_names_16 ofl_group_mod_cmd_names[] = {
        {OFPGC_ADD,    "add"},
        {OFPGC_MODIFY, "mod"},
        {OFPGC_DELETE, "del"}
};

static struct ofl_names_32 ofl_flow_wildcard_names[] = {
        {OFPFW_IN_PORT,     "in_port"},
        {OFPFW_DL_VLAN,     "dl_vlan"},
        {OFPFW_DL_VLAN_PCP, "dl_vlan_pcp"},
        {OFPFW_DL_TYPE,     "dl_type"},
        {OFPFW_NW_TOS,      "nw_tos"},
        {OFPFW_NW_PROTO,    "nw_proto"},
        {OFPFW_TP_SRC,      "tp_src"},
        {OFPFW_TP_DST,      "tp_dst"},
        {OFPFW_MPLS_LABEL,  "mpls_label"},
        {OFPFW_MPLS_TC,     "mpls_tc"},
        {OFPFW_ALL,         "all"}
        //OFPFW_ICMP_TYPE == OFPFW_TP_SRC
        //OFPFW_ICMP_CODE == OFPFW_TP_DST
};

static struct ofl_names_16 ofl_vlan_id_names[] = {
        {OFPVID_ANY,  "any"},
        {OFPVID_NONE, "none"}
        //OFP_VLAN_NONE == OFPVID_NONE
};

static struct ofl_names_16 ofl_match_type_names[] = {
        {OFPMT_STANDARD, "standard"}
};

static struct ofl_names_16 ofl_instruction_type_names[] = {
        {OFPIT_GOTO_TABLE,     "goto"},
        {OFPIT_WRITE_METADATA, "meta"},
        {OFPIT_WRITE_ACTIONS,  "write"},
        {OFPIT_APPLY_ACTIONS,  "apply"},
        {OFPIT_CLEAR_ACTIONS,  "clear"},
        {OFPIT_EXPERIMENTER,   "experim"}
};

static struct ofl_names_16 ofl_flow_mod_flag_names[] = {
        {OFPFF_SEND_FLOW_REM,  "send_rem"},
        {OFPFF_CHECK_OVERLAP, "check_overlap"}
};

static struct ofl_names_32 ofl_group_names[] = {
        {OFPG_ALL, "all"},
        {OFPG_ANY, "any"}
};

static struct ofl_names_8 ofl_group_type_names[] = {
        {OFPGT_ALL,      "all"},
        {OFPGT_SELECT,   "sel"},
        {OFPGT_INDIRECT, "ind"},
        {OFPGT_FF,       "ff"}
};

static struct ofl_names_8 ofl_flow_rem_reason_names[] = {
        {OFPRR_IDLE_TIMEOUT, "idle"},
        {OFPRR_HARD_TIMEOUT, "hard"},
        {OFPRR_DELETE,       "del"},
        {OFPRR_GROUP_DELETE, "group"}
};

static struct ofl_names_16 ofl_error_type_names[] = {
        {OFPET_HELLO_FAILED,         "HELLO_FAILED"},
        {OFPET_BAD_REQUEST,          "BAD_REQUEST"},
        {OFPET_BAD_ACTION,           "BAD_ACTION"},
        {OFPET_BAD_INSTRUCTION,      "BAD_INSTRUCTION"},
        {OFPET_BAD_MATCH,            "BAD_MATCH"},
        {OFPET_FLOW_MOD_FAILED,      "FLOW_MOD_FAILED"},
        {OFPET_GROUP_MOD_FAILED,     "GROUP_MOD_FAILED"},
        {OFPET_PORT_MOD_FAILED,      "PORT_MOD_FAILED"},
        {OFPET_TABLE_MOD_FAILED,     "TABLE_MOD_FAILED"},
        {OFPET_QUEUE_OP_FAILED,      "QUEUE_OP_FAILED"},
        {OFPET_SWITCH_CONFIG_FAILED, "SWITCH_CONFIG_FAILED"}
};

static struct ofl_names_16_16 ofl_error_code_names[] = {
        {OFPET_HELLO_FAILED,         OFPHFC_INCOMPATIBLE,          "INCOMPATIBLE"},
        {OFPET_HELLO_FAILED,         OFPHFC_EPERM,                 "EPERM"},

        {OFPET_BAD_REQUEST,          OFPBRC_BAD_VERSION,           "BAD_VERSION"},
        {OFPET_BAD_REQUEST,          OFPBRC_BAD_TYPE,              "BAD_TYPE"},
        {OFPET_BAD_REQUEST,          OFPBRC_BAD_STAT,              "BAD_STAT"},
        {OFPET_BAD_REQUEST,          OFPBRC_BAD_EXPERIMENTER,      "BAD_EXPERIMENTER"},
        {OFPET_BAD_REQUEST,          OFPBRC_BAD_SUBTYPE,           "BAD_SUBTYPE"},
        {OFPET_BAD_REQUEST,          OFPBRC_EPERM,                 "EPERM"},
        {OFPET_BAD_REQUEST,          OFPBRC_BAD_LEN,               "BAD_LEN"},
        {OFPET_BAD_REQUEST,          OFPBRC_BUFFER_EMPTY,          "BUFFER_EMPTY"},
        {OFPET_BAD_REQUEST,          OFPBRC_BUFFER_UNKNOWN,        "BUFFER_UNKNOWN"},
        {OFPET_BAD_REQUEST,          OFPBRC_BAD_TABLE_ID,          "BAD_TABLE_ID"},

        {OFPET_BAD_ACTION,           OFPBAC_BAD_TYPE,              "BAD_TYPE"},
        {OFPET_BAD_ACTION,           OFPBAC_BAD_LEN,               "BAD_LEN"},
        {OFPET_BAD_ACTION,           OFPBAC_BAD_EXPERIMENTER,      "BAD_EXPERIMENTER"},
        {OFPET_BAD_ACTION,           OFPBAC_BAD_EXPERIMENTER_TYPE, "BAD_EXPERIMENTER_TYPE"},
        {OFPET_BAD_ACTION,           OFPBAC_BAD_OUT_PORT,          "BAD_OUT_PORT"},
        {OFPET_BAD_ACTION,           OFPBAC_BAD_ARGUMENT,          "BAD_ARGUMENT"},
        {OFPET_BAD_ACTION,           OFPBAC_EPERM,                 "EPERM"},
        {OFPET_BAD_ACTION,           OFPBAC_TOO_MANY,              "TOO_MANY"},
        {OFPET_BAD_ACTION,           OFPBAC_BAD_QUEUE,             "BAD_QUEUE"},
        {OFPET_BAD_ACTION,           OFPBAC_BAD_OUT_GROUP,         "BAD_OUT_GROUP"},
        {OFPET_BAD_ACTION,           OFPBAC_UNSUPPORTED_ORDER,     "UNSUPPORTED_ORDER"},
        {OFPET_BAD_ACTION,           OFPBAC_BAD_TAG,               "BAD_TAG"},

        {OFPET_BAD_INSTRUCTION,      OFPBIC_UNKNOWN_INST,          "UNKNOWN_INST"},
        {OFPET_BAD_INSTRUCTION,      OFPBIC_UNSUP_INST,            "UNSUP_INST"},
        {OFPET_BAD_INSTRUCTION,      OFPBIC_BAD_TABLE_ID,          "BAD_TABLE_ID"},
        {OFPET_BAD_INSTRUCTION,      OFPBIC_UNSUP_METADATA,        "UNSUP_METADATA"},
        {OFPET_BAD_INSTRUCTION,      OFPBIC_UNSUP_METADATA_MASK,   "UNSUP_METADATA_MASK"},
        {OFPET_BAD_INSTRUCTION,      OFPBIC_UNSUP_EXP_INST,        "UNSUP_EXP_INST"},

        {OFPET_BAD_MATCH,            OFPBMC_BAD_TYPE,              "BAD_TYPE"},
        {OFPET_BAD_MATCH,            OFPBMC_BAD_LEN,               "BAD_LEN"},
        {OFPET_BAD_MATCH,            OFPBMC_BAD_TAG,               "BAD_TAG"},
        {OFPET_BAD_MATCH,            OFPBMC_BAD_DL_ADDR_MASK,      "BAD_DL_ADDR_MASK"},
        {OFPET_BAD_MATCH,            OFPBMC_BAD_NW_ADDR_MASK,      "BAD_NW_ADDR_MASK"},
        {OFPET_BAD_MATCH,            OFPBMC_BAD_WILDCARDS,         "BAD_WILDCARDS"},
        {OFPET_BAD_MATCH,            OFPBMC_BAD_FIELD,             "BAD_FIELD"},
        {OFPET_BAD_MATCH,            OFPBMC_BAD_VALUE,             "BAD_VALUE"},

        {OFPET_FLOW_MOD_FAILED,      OFPFMFC_UNKNOWN,              "UNKNOWN"},
        {OFPET_FLOW_MOD_FAILED,      OFPFMFC_TABLE_FULL,           "TABLE_FULL"},
        {OFPET_FLOW_MOD_FAILED,      OFPFMFC_BAD_TABLE_ID,         "BAD_TABLE_ID"},
        {OFPET_FLOW_MOD_FAILED,      OFPFMFC_OVERLAP,              "OVERLAP"},
        {OFPET_FLOW_MOD_FAILED,      OFPFMFC_EPERM,                "EPERM"},
        {OFPET_FLOW_MOD_FAILED,      OFPFMFC_BAD_TIMEOUT,          "BAD_TIMEOUT"},
        {OFPET_FLOW_MOD_FAILED,      OFPFMFC_BAD_COMMAND,          "BAD_COMMAND"},

        {OFPET_GROUP_MOD_FAILED,     OFPGMFC_GROUP_EXISTS,         "GROUP_EXISTS"},
        {OFPET_GROUP_MOD_FAILED,     OFPGMFC_INVALID_GROUP,        "INVALID_GROUP"},
        {OFPET_GROUP_MOD_FAILED,     OFPGMFC_WEIGHT_UNSUPPORTED,   "WEIGHT_UNSUPPORTED"},
        {OFPET_GROUP_MOD_FAILED,     OFPGMFC_OUT_OF_GROUPS,        "OUT_OF_GROUPS"},
        {OFPET_GROUP_MOD_FAILED,     OFPGMFC_OUT_OF_BUCKETS,       "OUT_OF_BUCKETS"},
        {OFPET_GROUP_MOD_FAILED,     OFPGMFC_CHAINING_UNSUPPORTED, "CHAINING_UNSUPPORTED"},
        {OFPET_GROUP_MOD_FAILED,     OFPGMFC_WATCH_UNSUPPORTED,    "UNSUPPORTED"},
        {OFPET_GROUP_MOD_FAILED,     OFPGMFC_LOOP,                 "LOOP"},
        {OFPET_GROUP_MOD_FAILED,     OFPGMFC_UNKNOWN_GROUP,        "UNKNOWN_GROUP"},

        {OFPET_PORT_MOD_FAILED,      OFPPMFC_BAD_PORT,             "BAD_PORT"},
        {OFPET_PORT_MOD_FAILED,      OFPPMFC_BAD_HW_ADDR,          "BAD_HW_ADDR"},
        {OFPET_PORT_MOD_FAILED,      OFPPMFC_BAD_CONFIG,           "BAD_CONFIG"},
        {OFPET_PORT_MOD_FAILED,      OFPPMFC_BAD_ADVERTISE,        "BAD_ADVERTISE"},

        {OFPET_TABLE_MOD_FAILED,     OFPTMFC_BAD_TABLE,            "BAD_TABLE"},
        {OFPET_TABLE_MOD_FAILED,     OFPTMFC_BAD_CONFIG,           "BAD_CONFIG"},

        {OFPET_QUEUE_OP_FAILED,      OFPQOFC_BAD_PORT,             "BAD_PORT"},
        {OFPET_QUEUE_OP_FAILED,      OFPQOFC_BAD_QUEUE,            "BAD_QUEUE"},
        {OFPET_QUEUE_OP_FAILED,      OFPQOFC_EPERM,                "EPERM"},

        {OFPET_SWITCH_CONFIG_FAILED, OFPSCFC_BAD_FLAGS,            "BAD_FLAGS"},
        {OFPET_SWITCH_CONFIG_FAILED, OFPSCFC_BAD_LEN,              "BAD_LEN"},
};

static struct ofl_names_16 ofl_stats_type_names[] = {
        {OFPST_DESC,         "desc"},
        {OFPST_FLOW,         "flow"},
        {OFPST_AGGREGATE,    "aggr"},
        {OFPST_TABLE,        "table"},
        {OFPST_PORT,         "port"},
        {OFPST_QUEUE,        "queue"},
        {OFPST_GROUP,        "grp"},
        {OFPST_GROUP_DESC,   "gdesc"},
        {OFPST_EXPERIMENTER, "experim"}
};

static struct ofl_names_16 ofl_stats_reply_flag_names[] = {
        {OFPSF_REPLY_MORE, "more"}
};

static struct ofl_names_16 ofl_flow_match_field_names[] = {
        {OFPFMF_IN_PORT,     "in_port"},
        {OFPFMF_DL_VLAN,     "dl_vlan"},
        {OFPFMF_DL_VLAN_PCP, "dl_vlan_pcp"},
        {OFPFMF_DL_TYPE,     "dl_type"},
        {OFPFMF_NW_TOS,      "nw_tos"},
        {OFPFMF_NW_PROTO,    "nw_proto"},
        {OFPFMF_TP_SRC,      "tp_src"},
        {OFPFMF_TP_DST,      "tp_dst"},
        {OFPFMF_MPLS_LABEL,  "mpls_label"},
        {OFPFMF_MPLS_TC,     "mpls_tc"},
        {OFPFMF_TYPE,        "type"},
        {OFPFMF_DL_SRC,      "dl_src"},
        {OFPFMF_DL_DST,      "dl_dst"},
        {OFPFMF_NW_SRC,      "nw_src"},
        {OFPFMF_NW_DST,      "nw_dst"},
        {OFPFMF_METADATA,    "metadata"}
};

static struct ofl_names_16 ofl_queue_properties_names[] = {
        {OFPQT_NONE,     "none"},
        {OFPQT_MIN_RATE, "min_rate"}
};



#endif /* OFL_NAMES_H */
