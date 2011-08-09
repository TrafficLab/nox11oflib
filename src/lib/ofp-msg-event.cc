#include "ofp-msg-event.hh"
#include "ofp-msg.hh"


namespace vigil {

Ofp_msg_event *
Ofp_msg_event::create_event(datapathid dpid, uint32_t xid, boost::shared_ptr<Ofp_msg> msg) {
    std::string name;
	switch ((**msg)->type) {
    	case OFPT_STATS_REPLY: {
    		name = get_stats_name(((struct ofl_msg_stats_reply_header *)**msg)->type);
    		break;
    	}
    	default: {
    		name = get_name((**msg)->type);
    	}
    }
	return new Ofp_msg_event(name, dpid, xid, msg);
}

std::string
Ofp_msg_event::get_name(enum ofp_type type) {

	switch(type) {
        case OFPT_HELLO: { return std::string("Hello_event"); }
        case OFPT_ERROR: { return std::string("Error_event"); }
        case OFPT_ECHO_REQUEST: { return std::string("Echo_request_event"); }
        case OFPT_ECHO_REPLY: { return std::string("Echo_reply_event"); }
        case OFPT_EXPERIMENTER: { return std::string("Experimenter_event"); }
        case OFPT_FEATURES_REPLY: { return std::string("Features_reply_event"); }
        case OFPT_GET_CONFIG_REPLY: { return std::string("Get_config_reply_event"); }
        case OFPT_FLOW_MOD: { return std::string("Flow_mod_event"); } // for flowtracker
        case OFPT_FLOW_REMOVED: { return std::string("Flow_removed_event"); }
        case OFPT_PORT_STATUS: { return std::string("Port_status_event"); }
        case OFPT_PACKET_IN: { return std::string("Packet_in_event"); }
        case OFPT_BARRIER_REPLY: { return std::string("Barrier_reply_event"); }
        case OFPT_QUEUE_GET_CONFIG_REPLY: { return std::string("Queue_get_config_reply_event"); }

        case OFPT_FEATURES_REQUEST:
        case OFPT_GET_CONFIG_REQUEST:
        case OFPT_SET_CONFIG:
        case OFPT_PACKET_OUT:
        case OFPT_GROUP_MOD:
        case OFPT_PORT_MOD:
        case OFPT_TABLE_MOD:
        case OFPT_STATS_REQUEST:
        case OFPT_STATS_REPLY:
        case OFPT_BARRIER_REQUEST:
        case OFPT_QUEUE_GET_CONFIG_REQUEST:
        default: {
            //TODO Log
            return std::string("");
        }
    }
}

std::string
Ofp_msg_event::get_stats_name(enum ofp_stats_types type) {

    switch(type) {
        case OFPST_DESC: { return std::string("Desc_stats_in_event"); }
        case OFPST_FLOW: { return std::string("Flow_stats_in_event"); }
        case OFPST_AGGREGATE: { return std::string("Aggregate_stats_in_event"); }
        case OFPST_TABLE: { return std::string("Table_stats_in_event"); }
        case OFPST_PORT: { return std::string("Port_stats_in_event"); }
        case OFPST_QUEUE: { return std::string("Queue_stats_in_event"); }
        case OFPST_GROUP: { return std::string("Group_stats_in_event"); }
        case OFPST_GROUP_DESC: { return std::string("Group_desc_stats_in_event"); }
        case OFPST_EXPERIMENTER: { return std::string("Experimenter_stats_in_event"); }
        default: {
            //TODO Log
            return std::string("");
        }
    }
}

} // namespace vigil
