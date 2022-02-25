#ifndef GENERALVALUE_H
#define GENERALVALUE_H
#include <string>
#include <vector>
#include "unit/sult_heads.h"

namespace _sutl {

template <class T>
inline void delete_ptr(T*_p){
    if(_p){
        delete  _p ;
        _p=nullptr;
    }
}
struct pair;
class General_Value
{
public:
    enum TYPE{
        EMPTY=0,
        INT,
        DOUBLE,
        STRING,
        BOOL,
        LIST,
        PAIR,
        ERROR,
    } ;
    typedef  std::vector<General_Value*> list;

    General_Value():m_type(INT),v_int(0){}
    General_Value(TYPE _type);
    General_Value(const General_Value& _gv);
    General_Value(const std::string&);
    ~General_Value();

    General_Value &operator=(const General_Value &);
    General_Value &operator=(int);
    General_Value &operator=(double);
    General_Value &operator=(bool);
    General_Value &operator=(const std::string &);
    General_Value &operator=(const pair &);
    General_Value &operator=(const list &);

    TYPE get_type(){return m_type;}
private:
    TYPE m_type;
    union {
        int             v_int;
        double          v_double;
        std::string*    v_string;
        bool            v_bool;
        pair*            v_pair;
        list*           v_list;
    };
    void copy_union(const General_Value &);
    void move_union(const General_Value &);
    int free_value_by_type();
    int create_value_by_type(TYPE );

    void set_type(TYPE _type){m_type=_type;}
    int check_type(TYPE);
};
struct pair{
    General_Value *key=new General_Value("");
    General_Value *value=nullptr;
    General_Value &operator=(const pair&_orther){
        *key=*_orther.key;
        *value=*_orther.value;
    }
    ~pair(){
        delete_ptr<General_Value>(key);
        delete_ptr<General_Value>(value);
    }
};
}


#endif // GENERALVALUE_H
