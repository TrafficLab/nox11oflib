#include "ofp-msg-event.hh"
#include "ofp-msg.hh"


namespace vigil {

Ofp_msg_event *
Ofp_msg_event::create_event(datapathid dpid, uint32_t xid, boost::shared_ptr<Ofp_msg> msg) {
    switch ((**msg)->type) {
        case OFPT_HELLO: { return new Ofp_msg_event(std::string("Hello_event"), dpid, xid, msg); }
        case OFPT_ERROR: { return new Ofp_msg_event(std::string("Error_event"), dpid, xid, msg); }
        case OFPT_ECHO_REQUEST: { return new Ofp_msg_event(std::string("Echo_request_event"), dpid, xid, msg); }
        case OFPT_ECHO_REPLY: { return new Ofp_msg_event(std::string("Echo_reply_event"), dpid, xid, msg); }
        case OFPT_EXPERIMENTER: {
            return new Ofp_msg_event(std::string("Experimenter_event"), dpid, xid, msg);
        }
        case OFPT_FEATURES_REPLY: { return new Ofp_msg_event(std::string("Features_reply_event"), dpid, xid, msg); }
        case OFPT_GET_CONFIG_REPLY: { return new Ofp_msg_event(std::string("Get_config_reply_event"), dpid, xid, msg); }
        case OFPT_PACKET_IN: { return new Ofp_msg_event(std::string("Packet_in_event"), dpid, xid, msg); }
        case OFPT_FLOW_MOD: { return new Ofp_msg_event(std::string("Flow_mod_event"), dpid, xid, msg); } // for flowtracker
        case OFPT_FLOW_REMOVED: { return new Ofp_msg_event(std::string("Flow_removed_event"), dpid, xid, msg); }
        case OFPT_PORT_STATUS: { return new Ofp_msg_event(std::string("Port_status_event"), dpid, xid, msg); }
        case OFPT_STATS_REPLY: {
            switch(((struct ofl_msg_stats_reply_header *)**msg)->type) {
                case OFPST_DESC: { return new Ofp_msg_event(std::string("Desc_stats_in_event"), dpid, xid, msg); }
                case OFPST_FLOW: { return new Ofp_msg_event(std::string("Flow_stats_in_event"), dpid, xid, msg); }
                case OFPST_AGGREGATE: { return new Ofp_msg_event(std::string("Aggregate_stats_in_event"), dpid, xid, msg); }
                case OFPST_TABLE: { return new Ofp_msg_event(std::string("Table_stats_in_event"), dpid, xid, msg); }
                case OFPST_PORT: { return new Ofp_msg_event(std::string("Port_stats_in_event"), dpid, xid, msg); }
                case OFPST_QUEUE: { return new Ofp_msg_event(std::string("Queue_stats_in_event"), dpid, xid, msg); }
                case OFPST_GROUP: { return new Ofp_msg_event(std::string("Group_stats_in_event"), dpid, xid, msg); }
                case OFPST_GROUP_DESC: { return new Ofp_msg_event(std::string("Group_desc_stats_in_event"), dpid, xid, msg); }
                case OFPST_EXPERIMENTER:
                default: {
                    //TODO Log
                    return NULL;
                }
            }
        }
        case OFPT_BARRIER_REPLY: { return new Ofp_msg_event(std::string("Barrier_reply_event"), dpid, xid, msg); }
        case OFPT_QUEUE_GET_CONFIG_REPLY: { return new Ofp_msg_event(std::string("Queue_get_config_reply_event"), dpid, xid, msg); }

        case OFPT_FEATURES_REQUEST:
        case OFPT_GET_CONFIG_REQUEST:
        case OFPT_SET_CONFIG:
        case OFPT_PACKET_OUT:
        case OFPT_GROUP_MOD:
        case OFPT_PORT_MOD:
        case OFPT_TABLE_MOD:
        case OFPT_STATS_REQUEST:
        case OFPT_BARRIER_REQUEST:
        case OFPT_QUEUE_GET_CONFIG_REQUEST:
        default: {
            //TODO Log
            return NULL;
        }
    }
}

} // namespace vigil
