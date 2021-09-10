#ifndef LOG_IF_H
#define LOG_IF_H
#define LOGLEVEL(x) LOG_LEVEL##x
#define LOG_(x) log_##x
#include <string>
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
enum LOG_TYPE{
    UNKOWN=0,
    LOG4PLUS=1,
};

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

    static Log_If *get_instance(LOG_TYPE _type,
                                    const std::string&_arg1="",
                                    const std::string&_arg2="");
    virtual ~Log_If();
protected:
    virtual void log_worker(LOG_LEVEL,const std::string&)=0;

    Log_If();
};

}
#endif // LOG_IF_H
