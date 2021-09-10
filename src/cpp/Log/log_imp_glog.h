#ifndef LOG_IMP_LOG4CPLUS_H
#define LOG_IMP_LOG4CPLUS_H
#include "log_if.h"
#include "glog/logging.h"
#include <map>

#define LOG_TRACE(f_n,l_n,c_p,e_i)     \
    _sutl::Log_Glog_Trace_func lltf(f_n,l_n,c_p,e_i)

#define LOG_TRACE1(f_n,l_n,c_p)     \
    _sutl::Log_Glog_Trace_func lltf(f_n,l_n,c_p)

#define LOG_TRACE2(f_n,l_n)     \
    _sutl::Log_Glog_Trace_func lltf(f_n,l_n)

#define LOG_TRACE3(f_n)     \
    _sutl::Log_Glog_Trace_func lltf(f_n)

#define LOG_TRACE4(f_n,e_i)     \
    _sutl::Log_Glog_Trace_func lltf(f_n,"","",e_i)

/**必须在可访问代码块下声明过LOG_TRACEx才可用 **/

#define LOG_FATAL(data)     \
    lltf.log_fatal(data)
#define LOG_ERROR(data)     \
    lltf.log_error(data)
#define LOG_WARN(data)     \
    lltf.log_warn(data)
#define LOG_INFO(data)     \
    lltf.log_info(data)
#define LOG_DEBUG(data)     \
    lltf.log_debug(data)
#define LOG_TRACE5(data)     \
    lltf.log_trace(data)

#endif // LOG_IMP_LOG4CPLUS_H
