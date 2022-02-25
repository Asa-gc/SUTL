#ifndef GENERAL_VALUE_H
#define GENERAL_VALUE_H
#include "unit/sult_heads.h"
#include <vector>
#include <map>

namespace _sutl {

class General_Value_Imp;
enum TYPE{
    INT=0,
    DOUBLE,
    STRING,
    BOOL,
    OBJECT,
    ARRAY,
};

class General_Value
{
public:
    typedef  std::map<std::string,General_Value_Imp> object;
    //typedef  std::map<std::string,std::string> atti;
    typedef  std::vector<General_Value_Imp> array;

    explicit General_Value(General_Value_Imp *_imp=nullptr);

    General_Value &operator=(const General_Value &);
    General_Value &operator=(int);
    General_Value &operator=(double);
    General_Value &operator=(bool);
    General_Value &operator=(const std::string &);
    General_Value &operator=(const object &);
    General_Value &operator=(const array &);

protected:
    General_Value_Imp *m_imp=nullptr;
};

}
#endif // GENERAL_VALUE_H
