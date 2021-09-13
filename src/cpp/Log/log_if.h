#ifndef LOG_IF_H
#define LOG_IF_H
#define LOGLEVEL(x) LOG_LEVEL##x
#define LOG_(x) log_##x
#include <string>
#include <map>
#include <iostream>

#ifndef DEFECT_LOG_TYPE
#define DEFECT_LOG_TYPE "GLOG"
#endif

namespace  _sutl{
enum LOG_LEVEL{
    LOGLEVEL(OFF)=0,
    LOGLEVEL(FATAL)=1,
    LOGLEVEL(ERROR)=2,
    LOGLEVEL(WARN)=3,
    LOGLEVEL(INFO)=4,
    LOGLEVEL(DEBUG)=5,
    LOGLEVEL(TRACE)=6,
    LOGLEVEL(ALL)=7,
};
class Log_If;

class Log_Imp{
public:
    virtual ~Log_Imp();
    virtual void log_worker(LOG_LEVEL,const std::string&)=0;
protected:
    Log_Imp();
};
typedef Log_Imp* (*instance)(const std::map<std::string,std::string>&_arg2);

class Log_If
{
public:
    void LOG_(fatal)(const std::string&_data){
        this->log_worker(LOGLEVEL(FATAL),_data);
    }
    void LOG_(error)(const std::string&_data){
        this->log_worker(LOGLEVEL(ERROR),_data);
    }
    void LOG_(warn)(const std::string&_data){
        this->log_worker(LOGLEVEL(WARN),_data);
    }
    void LOG_(info)(const std::string&_data){
        this->log_worker(LOGLEVEL(INFO),_data);
    }
    void LOG_(debug)(const std::string&_data){
        this->log_worker(LOGLEVEL(DEBUG),_data);
    }
    void LOG_(trace)(const std::string&_data){
        this->log_worker(LOGLEVEL(TRACE),_data);
    }
    static Log_If *get_log(const std::string& _type="",
                           const std::map<std::string,std::string>&_arg
                           =std::map<std::string,std::string>(),
                           bool _newFlag=false);
    static bool regist_instance(const std::string& _type,instance _instanceFuc);

    virtual ~Log_If();

    std::string get_type(){return m_type;}
    std::string set_type(const std::string&_type){
        if(!_type.empty()&&m_type!=_type){
            if(nullptr!=m_logImp){
                delete m_logImp;
                m_logImp=nullptr;
            }
            m_type=_type;
        }
        return m_type;
    }
    void log_worker(LOG_LEVEL _ll,const std::string&_data){
        if(nullptr==m_logImp){
            m_logImp=get_instance();
            if(nullptr==m_logImp){
                std::cout<<"m_logImp instance fail!"<<std::endl;
                return;
            }
        }
        m_logImp->log_worker(_ll,_data);
    }
protected:
    Log_Imp *get_instance(const std::string& _type="",
                          const std::map<std::string,std::string>&_arg
                          =std::map<std::string,std::string>());
    Log_If();
    static std::map<std::string,instance> m_registList;
    static Log_If *s_log;

    Log_Imp *m_logImp=nullptr;
    std::string m_type=DEFECT_LOG_TYPE;
    std::map<std::string,std::string> m_arg;//todo 实装
};

class Log_Trace
{
public:
    Log_Trace(const std::string &_func_name,
              const std::string &_ext_inf=""){
        m_func_name=_func_name;
        std::string data="\t"+m_func_name;
        if(!_ext_inf.empty()){
            data+=(" \t[EXT_INF: "+_ext_inf);
        }
        data+=+" \t[START]";
        if(nullptr==s_loger){
            s_loger=Log_If::get_log(DEFECT_LOG_TYPE);
        }
        s_loger->LOG_(trace)(data);
    }
    ~Log_Trace(){
        if(nullptr==s_loger){
            s_loger=Log_If::get_log(DEFECT_LOG_TYPE);
        }
        s_loger->LOG_(trace)("\t"+m_func_name+" \t[END]");
    }

    void log_worker(LOG_LEVEL _ll,const std::string&_data){
        s_loger->log_worker(_ll,_data);
    }
private:
    Log_Trace(){}
    std::string m_func_name;

    Log_If *s_loger=nullptr;
};
}
#endif // LOG_IF_H
