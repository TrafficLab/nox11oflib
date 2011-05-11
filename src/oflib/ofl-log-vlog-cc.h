#ifndef OFL_LOG_VLOG_CC_H
#define OFL_LOG_VLOG_CC_H

#include "vlog.hh"

#define VLOG_NAME(NAME) lg_##NAME

#define OFL_LOG_INIT(MODULE) \
        vigil::Vlog_module VLOG_NAME(MODULE)("MODULE");

#define OFL_LOG_DBG(MODULE, ...) \
    VLOG_NAME(MODULE).dbg(__VA_ARGS__)

#define OFL_LOG_WARN(MODULE, ...) \
    VLOG_NAME(MODULE).warn(__VA_ARGS__)

#define OFL_LOG_IS_DBG_ENABLED(MODULE) \
    VLOG_NAME(MODULE).is_dbg_enabled()

#define OFL_LOG_IS_WARN_ENABLED(MODULE) \
    VLOG_NAME(MODULE).is_warn_enabled()

#endif /* OFL_LOG_VLOG_CC_H */
