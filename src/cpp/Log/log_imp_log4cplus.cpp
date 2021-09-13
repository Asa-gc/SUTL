#include "log_imp_log4cplus.h"
#include<string.h>
namespace _sutl {
int c2wc(const char* _chars,unsigned int _len,wchar_t*& _wchar_ts)
{
    if(0==_len){
        return -1;
    }
    _len += 1;
    size_t converted = 0;
    _wchar_ts=(wchar_t*)malloc(_len*sizeof(wchar_t));
    int ddd=_len*sizeof(wchar_t);
    memset( _wchar_ts, 0, _len*sizeof(wchar_t));
    mbstowcs_s(&converted, _wchar_ts, _len, _chars, _TRUNCATE);
    return 0;
}

log4cplus::Initializer *g_initializer=nullptr;
Initializer_Manager *Initializer_Manager::g_initializer_manager=nullptr;
bool Initializer_Manager::g_init=false;

Initializer_Manager::Initializer_Manager(){
    if(nullptr==g_initializer){
        g_initializer=new log4cplus::Initializer;
    }
    g_init=true;
}

Initializer_Manager::~Initializer_Manager(){
    if(nullptr==g_initializer){
        delete g_initializer;
        g_initializer=nullptr;
    }
    g_init=false;
}

Log_Log4cplus::Log_Log4cplus(const log4cplus::tstring &_name,
                                     const log4cplus::tstring &_config_path)
{
    Initializer_Manager::init_Initializer_Manager();
    if(false==_config_path.empty()){//_config_path非空
        log4cplus::PropertyConfigurator::doConfigure(_config_path);
    }

    if(_name.empty()){
        m_loger=log4cplus::Logger::getRoot();
    }else {
        m_loger=log4cplus::Logger::getInstance(_name);
    }
}

Log_Log4cplus::~Log_Log4cplus()
{
}

void Log_Log4cplus::log_worker(LOG_LEVEL _ll, const log4cplus::tstring &_data)
{
    switch (_ll) {
    case LOGLEVEL(FATAL):
        LOG4CPLUS_FATAL(m_loger,_data);
        break;
    case LOGLEVEL(ERROR):
        LOG4CPLUS_ERROR(m_loger,_data);
        break;
    case LOGLEVEL(WARN):
        LOG4CPLUS_WARN(m_loger,_data);
        break;
    case LOGLEVEL(INFO):
        LOG4CPLUS_INFO(m_loger,_data);
        break;
    case LOGLEVEL(DEBUG):
        LOG4CPLUS_DEBUG(m_loger,_data);
        break;
    case LOGLEVEL(TRACE):
        LOG4CPLUS_TRACE(m_loger,_data);
        break;
    default:
        break;
    }
}


Log_Log4cplus *Log_Log4cplus_Trace_func::s_loger=nullptr;

Log_Log4cplus_Trace_func::Log_Log4cplus_Trace_func(const log4cplus::tstring &_func_name,
                                                   const log4cplus::tstring &_loger_name,
                                                   const log4cplus::tstring &_config_path,
                                                   const log4cplus::tstring &_ext_inf):m_func_name(_func_name)
{
    Initializer_Manager::init_Initializer_Manager();
    this->trace_log_worker(_func_name,_loger_name,_config_path,_ext_inf);
}

void Log_Log4cplus_Trace_func::log_worker(LOG_LEVEL _ll, const std::string &_data){
    if(nullptr!=s_loger){
        s_loger->log_worker(_ll,_data);
    }
}

void Log_Log4cplus_Trace_func::trace_log_worker(const log4cplus::tstring &_func_name,
                                                const log4cplus::tstring &_loger_name,
                                                const log4cplus::tstring &_config_path,
                                                const log4cplus::tstring &_ext_inf)
{

    m_func_name=_func_name;
    m_loger_name=_loger_name;
    log4cplus::tstring data=m_func_name;
    if(!_ext_inf.empty()){
        data+=(LOG4CPLUS_TEXT(" \t[EXT_INF: ")+_ext_inf+LOG4CPLUS_TEXT("]"));
    }
    data+=LOG4CPLUS_TEXT(" \tSTART");
    if(nullptr==s_loger){
        s_loger=new Log_Log4cplus(_loger_name,_config_path);
    }
    s_loger->log_worker(LOG_LEVEL::LOGLEVEL(TRACE),data);
}

Log_Log4cplus_Trace_func::~Log_Log4cplus_Trace_func()
{
    log4cplus::tstring data=m_func_name;
    data+=LOG4CPLUS_TEXT(" \tEND");
    s_loger->log_worker(LOG_LEVEL::LOGLEVEL(TRACE),data);
}

}
