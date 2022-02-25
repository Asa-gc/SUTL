#include "general_value.h"

namespace _sutl {

General_Value::General_Value(General_Value::TYPE _type):m_type(INT){
    create_value_by_type(_type);
}

General_Value::General_Value(const General_Value &_gv):
    m_type(INT){
    copy_union(_gv);
}

General_Value::General_Value(const std::string &):m_type(INT){
    create_value_by_type(TYPE::STRING);
}

General_Value::~General_Value(){
    free_value_by_type();
}

void General_Value::copy_union(const General_Value &_gv)
{
    check_type(_gv.m_type);
    switch (_gv.m_type) {
    case TYPE::INT: this->v_int=_gv.v_int; break;
    case TYPE::DOUBLE: this->v_double=_gv.v_double; break;
    case TYPE::STRING: create_value_by_type(TYPE::STRING);
                *v_string=*_gv.v_string; break;
    case TYPE::BOOL: this->v_bool=_gv.v_bool; break;
    case TYPE::LIST:{
        create_value_by_type(TYPE::LIST);
        int size=_gv.v_list->size();
        for(int i=0;i<size;++i){
            General_Value *t=
                    new General_Value(*(*_gv.v_list)[i]);
            v_list->push_back(t);
        }
        break;
    }
    case TYPE::PAIR:create_value_by_type(TYPE::PAIR);
        v_pair=_gv.v_pair;
        break;

    }
    m_type= _gv.m_type;
}

void General_Value::move_union(const General_Value &_gv)
{

}
int General_Value::free_value_by_type()
{
    if(TYPE::STRING==m_type){
        delete_ptr<std::string>(v_string);
     }else if(TYPE::LIST==m_type){
        int size=v_list->size();
        for(int i=0;i<size;++i){
            delete_ptr<General_Value>((*v_list)[i]);
        }
         delete_ptr<list>(v_list);
     }else if(TYPE::PAIR==m_type){
         delete_ptr<pair>(v_pair);
     }
     m_type=EMPTY;
     return RET_OK;
}

int General_Value::create_value_by_type(General_Value::TYPE _type)
{
    check_type(_type);
    switch (_type) {
    case TYPE::STRING: v_string=new std::string(""); break;
    case TYPE::LIST:   v_list=new list; break;
    case TYPE::PAIR:   v_pair=new pair; break;
    }
    m_type=_type;
    return RET_OK;
}

int General_Value::check_type(General_Value::TYPE _type)
{
    if(this->m_type==_type){
        return RET_OK;
    }
    free_value_by_type();
    return RET_NG;
}

General_Value &General_Value::operator=(const General_Value &_gv){
    copy_union(_gv);
    return *this;
}

General_Value &General_Value::operator=(int _v){
    check_type(TYPE::INT);
    this->v_int=_v;
    this->m_type=TYPE::INT;
    return *this;
}

General_Value &General_Value::operator=(double _v){
    check_type(TYPE::DOUBLE);
    this->v_double=_v;
    this->m_type=TYPE::DOUBLE;
    return *this;
}

General_Value &General_Value::operator=(const std::string& _v){
    if(RET_OK!=check_type(TYPE::STRING)){
        create_value_by_type(TYPE::STRING);
    }
    *this->v_string=_v;
    this->m_type=TYPE::STRING;
    return *this;
}

General_Value &General_Value::operator=(const pair &_v)
{
    if(RET_OK!=check_type(TYPE::PAIR)){
        create_value_by_type(TYPE::PAIR);
    }
    *this->v_pair=_v;
    this->m_type=TYPE::PAIR;
    return *this;
}

General_Value &General_Value::operator=(const General_Value::list &_v)
{

    if(RET_OK!=check_type(TYPE::LIST)){
        create_value_by_type(TYPE::LIST);
    }

    v_list->clear();
    int size=_v.size();
    for(int i=0;i<size;++i){
        General_Value *t=
                new General_Value(*(_v[i]));
        v_list->push_back(t);
    }

    this->m_type=TYPE::LIST;
    return *this;
}

General_Value &General_Value::operator=(bool _v){
    check_type(TYPE::BOOL);
    this->v_bool=_v;
    this->m_type=TYPE::BOOL;
    return *this;
}

}
