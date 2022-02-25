#include "log_imp_glog.h"
#include<string.h>

#include<direct.h>
#include<io.h>

namespace _sutl {
Log_Imp_Glog *Log_Imp_Glog::s_glog=nullptr;
Log_Imp* glogInstance(const std::map<std::string, std::string> &_arg2);
bool reg=Log_If::regist_instance("GLOG",glogInstance);

Log_Imp* glogInstance(const std::map<std::string,std::string> &_arg2){
    return Log_Imp_Glog::get_instance(_arg2);
}
void Log_Imp_Glog::log_worker(LOG_LEVEL _ll, const std::string &_data)
{switch (_ll) {
    case LOGLEVEL(FATAL):
        LOG(FATAL)<<_data;
        break;
    case LOGLEVEL(DEBUG):
    case LOGLEVEL(WARN):
        LOG(WARNING)<<_data;
        break;
    case LOGLEVEL(TRACE):
    case LOGLEVEL(INFO):
        LOG(INFO)<<_data;
        break;
    case LOGLEVEL(ERROR):
    default:
        LOG(ERROR)<<_data;
        break;
    }
}

Log_Imp_Glog::Log_Imp_Glog(const std::string &_log_dir, const std::string &_log_file,
                           const std::string &_log_severitie)
{
    google::InitGoogleLogging(_log_dir.c_str());
    if (access(_log_dir.c_str(), 0) == -1)//
    {
        mkdir(_log_dir.c_str());
    }
    FLAGS_log_dir =_log_dir;
    google::SetLogDestination(google::INFO,"");
    google::SetLogDestination(google::WARNING,"");
    google::SetLogDestination(google::ERROR,"");

    if(""==_log_severitie||"INFO"==_log_severitie){
        google::SetLogDestination(google::INFO,_log_file.c_str());
    }else if("WARNING"==_log_severitie){
        google::SetLogDestination(google::WARNING,_log_file.c_str());
    }else if("ERROR"==_log_severitie){
        google::SetLogDestination(google::ERROR,_log_file.c_str());
    }
}
Log_Imp_Glog::~Log_Imp_Glog()
{
    google::ShutdownGoogleLogging();
}


}
