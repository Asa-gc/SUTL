#ifndef LOGAPI_H
#define LOGAPI_H
#include "log_if.h"

#define LOG_TRACE(f_n,e_i)     \
    _sutl::Log_Trace logTrace(f_n,e_i)

#define LOG_TRACE3(f_n)     \
    LOG_TRACE(f_n,"")

/**必须在可访问代码块下声明过LOG_TRACEx才可用 **/
#define LOG_FATAL(data)     \
    logTrace.log_worker(_sutl::LOGLEVEL(FATAL),data)
#define LOG_ERROR(data)     \
    logTrace.log_worker(_sutl::LOGLEVEL(ERROR),data)
#define LOG_WARN(data)     \
    logTrace.log_worker(_sutl::LOGLEVEL(WARN),data)
#define LOG_INFO(data)     \
    logTrace.log_worker(_sutl::LOGLEVEL(INFO),data)
#define LOG_DEBUG(data)     \
    logTrace.log_worker(_sutl::LOGLEVEL(DEBUG),data)
#define LOG_TRACE5(data)     \
    logTrace.log_worker(_sutl::LOGLEVEL(TRACE),data)


#endif // LOGAPI_H
