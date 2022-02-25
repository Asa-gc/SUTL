#include "log_if.h"
#include<io.h>

namespace _sutl {
Log_Imp::Log_Imp(){}
Log_Imp::~Log_Imp(){}
std::map<std::string,instance> Log_If::m_registList;
Log_If *Log_If::s_log=nullptr;
Log_If::Log_If(){}
Log_If::~Log_If(){
    if(nullptr!=m_logImp){
        delete  m_logImp;
        m_logImp=nullptr;
    }
}
Log_Imp *Log_If::get_instance(const std::string & _type,
                              const std::map<std::string,std::string> &_arg)
{
    set_type(_type);
    if(m_registList.find(m_type)!=m_registList.end()){
        return m_registList[m_type](_arg);
    }
    return nullptr;
}
Log_If *Log_If::get_log(const std::string& _type,
                        const std::map<std::string,std::string>&_arg,
                        bool _newFlag){
    (void)_arg;

    if(true==_newFlag){
        Log_If *tli=new Log_If;
        tli->set_type(_type);
        return tli;
    }
    if(nullptr==s_log){
        s_log=new Log_If();
        s_log->set_type(_type);
    }
    return s_log;
}
bool Log_If::regist_instance(const std::string& _type,instance _instanceFuc){
    //TODO_A warnning if key ${_type} exist in m_registList;
    m_registList[_type]=_instanceFuc;
    return true;
}


bool do_trace(){
    if(0==_access("./configs/ResultStorage/TRACE",0)){
        return true;
    }
    return false;
}
static const bool g_trace_flag=do_trace();
Log_Trace::Log_Trace(const std::string &_func_name,
          const std::string &_ext_inf){
    m_func_name=_func_name;
    if(false==g_trace_flag){
        return;
    }
    std::string data="\t"+m_func_name;
    if(!_ext_inf.empty()){
        data+=(" \t[EXT_INF: "+_ext_inf);
    }
    data+=+" \t[START]";
    if(nullptr==s_loger){
        s_loger=Log_If::get_log(DEFAULT_LOG_TYPE);
    }
    s_loger->LOG_(trace)(data);
}
Log_Trace::~Log_Trace(){
    if(false==g_trace_flag){
        return;
    }
    if(nullptr==s_loger){
        s_loger=Log_If::get_log(DEFAULT_LOG_TYPE);
    }
    s_loger->LOG_(trace)("\t"+m_func_name+" \t[END]");
}

}
