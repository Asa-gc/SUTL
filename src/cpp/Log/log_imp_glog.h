#ifndef LOG_IMP_LOG4CPLUS_H
#define LOG_IMP_LOG4CPLUS_H
#include "log_if.h"
#include "glog/logging.h"
#include <map>
namespace _sutl {
class Log_Imp_Glog:public Log_Imp{
public:
    virtual ~Log_Imp_Glog();
    virtual void log_worker(LOG_LEVEL _ll, const std::string&_data);
    static Log_Imp_Glog* get_instance(const std::map<std::string, std::string> &_log_arg=
            std::map<std::string, std::string>())
    {
        std::string log_dir="./logs";
        if(_log_arg.find("log_dir")!=_log_arg.end()){
           // log_dir=_log_arg.at("log_dir");
        }
        std::string log_file="./logs/logs.log";
        if(_log_arg.find("log_file")!=_log_arg.end()){
           // log_file=_log_arg.at("log_file");
        }
        std::string log_severitie="";
        if(_log_arg.find("log_severitie")!=_log_arg.end()){
            //log_severitie=_log_arg.at("log_file");
        }
        if(nullptr==s_glog){
            s_glog=new Log_Imp_Glog(log_dir,log_file,log_severitie);
        }
        return s_glog;
    }
protected:
    Log_Imp_Glog(const std::string& _log_dir,
                 const std::string& _log_file="", const std::string &_log_severitie="");
    static Log_Imp_Glog *s_glog;
};

}

#endif // LOG_IMP_LOG4CPLUS_H
