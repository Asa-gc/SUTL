#include "log_if.h"
#include "log_imp_log4cplus.h"
namespace _sutl {
Log_If::Log_If()
{

}
Log_If *Log_If::get_instance(LOG_TYPE _type, const std::string &_arg1,
                                 const std::string &_arg2)
{
    Log_If * ret=nullptr;
    switch (_type) {
    case 0:

        break;
    case 1:
        ret=new Log_Log4cplus(_arg1,_arg2);
        break;
    }
    return ret;
}

Log_If::~Log_If()
{

}
}
