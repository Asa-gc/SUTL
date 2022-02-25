#include "general_value.h"
#include "general_value_imp.h"

namespace _sutl {

General_Value::General_Value(General_Value_Imp *_imp):m_imp(_imp){

}

General_Value &General_Value::operator=(const General_Value &_gv)
{
    *m_imp=*(_gv.m_imp);
    return *this;
}

General_Value &General_Value::operator=(int _v)
{
    *m_imp=_v;
    return *this;
}
General_Value &General_Value::operator=(double _v)
{
    *m_imp=_v;
    return *this;
}
General_Value &General_Value::operator=(bool _v)
{
    *m_imp=_v;
    return *this;
}
General_Value &General_Value::operator=(const std::string & _v)
{
    *m_imp=_v;
    return *this;
}
General_Value &General_Value::operator=(const object & _v)
{
    *m_imp=_v;
    return *this;
}
General_Value &General_Value::operator=(const array & _v)
{
    *m_imp=_v;
    return *this;
}

}
