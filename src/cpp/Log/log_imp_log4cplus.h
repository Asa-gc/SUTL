#ifndef LOG_IMP_LOG4CPLUS_H
#define LOG_IMP_LOG4CPLUS_H
#include "log_if.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/initializer.h>
#include <map>
namespace _sutl {

class Initializer_Manager{
public:
    ~Initializer_Manager();
    static bool get_init_status(){
        return g_init;
    }
    static void init_Initializer_Manager(){
        if(nullptr==g_initializer_manager){
            g_initializer_manager=new Initializer_Manager();
        }
    }
private:

    Initializer_Manager();
    static Initializer_Manager *g_initializer_manager;

    static bool g_init;
};
class Log_Log4cplus : public Log_If
{
public:
    explicit Log_Log4cplus(const log4cplus::tstring &_name=LOG4CPLUS_TEXT(""),
                      const log4cplus::tstring &_config_path=LOG4CPLUS_TEXT("config.properties"));
    ~Log_Log4cplus();
protected:
    virtual void log_worker(LOG_LEVEL,const log4cplus::tstring&);

private:
    log4cplus::Logger m_loger;
    friend class Log_Log4cplus_Trace_func;
};
class Log_Log4cplus_Trace_func:public Log_If//使用组合替代继承。TODO 待添加锁
{
public:
    ~Log_Log4cplus_Trace_func();

    Log_Log4cplus_Trace_func(const std::string &_func_name,
                             const std::string &_loger_name="",
                             const std::string &_config_path="config.properties",
                             const std::string &_ext_inf="");

protected:
    virtual void log_worker(LOG_LEVEL _ll,const std::string&_data);
private:
    void trace_log_worker(const log4cplus::tstring &_func_name,
                    const log4cplus::tstring &_loger_name=LOG4CPLUS_TEXT(""),
                    const log4cplus::tstring &_config_path=LOG4CPLUS_TEXT("config.properties"),
                    const log4cplus::tstring &_ext_inf=LOG4CPLUS_TEXT(""));


    log4cplus::tstring m_func_name;
    log4cplus::tstring m_loger_name;

    static Log_Log4cplus *s_loger;
};

}
#define LOG_TRACE(f_n,l_n,c_p,e_i)     \
    _sutl::Log_Log4cplus_Trace_func lltf(f_n,l_n,c_p,e_i)

#define LOG_TRACE1(f_n,l_n,c_p)     \
    _sutl::Log_Log4cplus_Trace_func lltf(f_n,l_n,c_p)

#define LOG_TRACE2(f_n,l_n)     \
    _sutl::Log_Log4cplus_Trace_func lltf(f_n,l_n)

#define LOG_TRACE3(f_n)     \
    _sutl::Log_Log4cplus_Trace_func lltf(f_n)

#define LOG_TRACE4(f_n,e_i)     \
    _sutl::Log_Log4cplus_Trace_func lltf(f_n,LOG4CPLUS_TEXT(""),LOG4CPLUS_TEXT("config.properties"),e_i)

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
