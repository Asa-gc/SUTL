#ifndef SUTL_NJSON_DOC_H
#define SUTL_NJSON_DOC_H
#include "sutl_njson_tools.h"

#define WITH_MUTEX
#ifdef WITH_MUTEX
#include <mutex>
#define Doc_Get_Value_Func_Helper(type,empty)  \
    int get_value(const std::string &_key, empty##type &_value,const empty##type &_def_err_val= empty##type (),\
                  const conditions &_conditions=conditions(),int _index=-1){\
    std::lock_guard<std::mutex> lg(m_data_mutex);\
    return NJSON_TOOLS->get_value(m_data,_key,_value,_def_err_val,_conditions,_index);\
    }
#define Doc_Set_Value_Func_Helper(type,empty)  \
    int set_value(const std::string &_key, empty##type _value,\
                      const conditions &_conditions=conditions(),int _index=-1){\
    std::lock_guard<std::mutex> lg(m_data_mutex);\
    return NJSON_TOOLS->set_value(m_data,_key,_value,_conditions,_index);\
    }
#else
#define Doc_Get_Value_Func_Helper(type,empty)  \
    int get_value(const std::string &_key, empty##type &_value,const empty##type &_def_err_val= empty##type (),\
                  const conditions &_conditions=conditions(),int _index=-1){\
    return NJSON_TOOLS->get_value(m_data,_key,_value,_def_err_val,_conditions,_index);\
    }
#define Doc_Set_Value_Func_Helper(type,empty)  \
    int set_value(const std::string &_key, empty##type _value,\
                      const conditions &_conditions=conditions(),int _index=-1){\
    return NJSON_TOOLS->set_value(m_data,_key,_value,_conditions,_index);\
    }
#endif
#define Doc_Get_Value_Func(type)  Doc_Get_Value_Func_Helper(type, )
#define Doc_Set_Value_Func(type)  Doc_Set_Value_Func_Helper(type, )

namespace _sutl {
class Sutl_Njson_Doc{
public:
    int set_str(const std::string &_str){
        return NJSON_TOOLS->parse(m_data,_str);
    }
    std::string get_str(int _indent=-1){
        return NJSON_TOOLS->get_str(m_data,_indent);
    }
    Doc_Get_Value_Func(int)
    Doc_Get_Value_Func(double)
    Doc_Get_Value_Func(bool)
    Doc_Get_Value_Func(std::string)
    Doc_Get_Value_Func(json_object)
    Doc_Get_Value_Func(json_array)

    Doc_Set_Value_Func(int)
    Doc_Set_Value_Func(double)
    Doc_Set_Value_Func(bool)
    Doc_Set_Value_Func(const std::string&)
    Doc_Set_Value_Func(const json_object&)
    Doc_Set_Value_Func(const json_array&)

private:
    njson m_data;
#ifdef WITH_MUTEX
    std::mutex m_data_mutex;
#endif
    int m_has_err=RET_OK;
};
}
#endif // SUTL_NJSON_DOC_H
