#ifndef NJSON_TOOLS_H
#define NJSON_TOOLS_H
#include "../sutl_heads.h"
#include <string>
#include <queue>
#include <vector>
#define NJSON_TOOLS _sutl::Njson_Tool::get_instance()

#define Get_Value_Func_Helper(type,empty)  \
    int get_value(njson& _j,const std::string &_key, empty##type &_value,const empty##type &_def_err_val= empty##type (),\
                  const conditions &_conditions=conditions(),int _index=-1){\
        _value=_def_err_val;\
        njson_data_ptr_container ndpc=find_njson_value_ex(_j,_key,_conditions,_index);\
        return ndpc.get_val(_value);\
    }
#define Get_Value_Func(type)  Get_Value_Func_Helper(type, )

#define Set_Value_Func_Helper(type,empty)  \
    int set_value(njson& _j,const std::string &_key, empty##type _value,\
                  const conditions &_conditions=conditions(),int _index=-1){\
        njson_data_ptr_container ndpc=find_njson_value_ex(_j,_key,_conditions,_index);\
        return ndpc.set_val(_value);\
    }
#define Set_Value_Func(type)  Set_Value_Func_Helper(type, )

using njson = nlohmann::json;
using json_object = njson::object_t;
using json_array = njson::array_t;

using conditions = std::vector<std::string>;
//Self Use Tool Lib
namespace _sutl {
class Njson_Tool {
public:
    static Njson_Tool* get_instance(){
        if(nullptr==s_njson_tool){s_njson_tool=new Njson_Tool;}
        return s_njson_tool;
    }

    std::string  get_str(const njson &_j,int _indent=-1,char _indent_char=' '){
        return _j.dump(_indent,_indent_char,false,njson::error_handler_t::ignore);
    }
    int parse(njson &_j,const std::string &_str){
        _j=njson::parse(_str,nullptr);
        return  _j.is_discarded()?RET_NG_ARG:RET_OK;
    }


    Get_Value_Func(int)
    Get_Value_Func(double)
    Get_Value_Func(bool)
    Get_Value_Func(std::string)
    Get_Value_Func(json_object)
    Get_Value_Func(json_array)


    Set_Value_Func(int)
    Set_Value_Func(double)
    Set_Value_Func(bool)
    Set_Value_Func(const std::string&)
    Set_Value_Func(const json_object&)
    Set_Value_Func(const json_array&)

protected:
    enum PTR_TYPE {
        void_ptr,
        object_ptr,
        array_ptr,
        string_ptr,
        binary_ptr,
        boolean_ptr,
        integer_ptr,
        uinteger_ptr,
        float_ptr,
    };

    struct njson_data_ptr_container {
        PTR_TYPE type = void_ptr;
        void* ptr = nullptr;

        njson_data_ptr_container() :type(void_ptr), ptr(nullptr) {}
        njson_data_ptr_container(njson&_j) { this->set_njson_ptr(_j); }
        njson_data_ptr_container(const njson_data_ptr_container&_ndpc) :type(_ndpc.type), ptr(_ndpc.ptr) {}
        void operator=(const njson_data_ptr_container&_ndpc) { type = _ndpc.type; ptr = _ndpc.ptr; }

        void set_nullptr() { type = void_ptr; ptr = nullptr; }
        void set_ptr(njson::object_t*_ptr) { if (nullptr == _ptr) { return set_nullptr(); }type = object_ptr; ptr = _ptr; }
        void set_ptr(njson::array_t*_ptr) { if (nullptr == _ptr) { return set_nullptr(); }type = array_ptr; ptr = _ptr; }
        void set_ptr(njson::string_t*_ptr) { if (nullptr == _ptr) { return set_nullptr(); }type = string_ptr; ptr = _ptr; }
        void set_ptr(njson::binary_t*_ptr) { if (nullptr == _ptr) { return set_nullptr(); }type = binary_ptr; ptr = _ptr; }
        void set_ptr(njson::boolean_t*_ptr) { if (nullptr == _ptr) { return set_nullptr(); }type = boolean_ptr; ptr = _ptr; }
        void set_ptr(njson::number_integer_t*_ptr) { if (nullptr == _ptr) { return set_nullptr(); }type = integer_ptr; ptr = _ptr; }
        void set_ptr(njson::number_unsigned_t*_ptr) { if (nullptr == _ptr) { return set_nullptr(); }type = uinteger_ptr; ptr = _ptr; }
        void set_ptr(njson::number_float_t*_ptr) { if (nullptr == _ptr) { return set_nullptr(); }type = float_ptr; ptr = _ptr; }
        void set_njson_ptr(njson &_j) {
            //        if(_j.is_null()||_j.is_discarded()){ return set_nullptr();}
            if (_j.is_array()) { return set_ptr(_j.get_ptr<njson::array_t*>()); }
            if (_j.is_object()) { return set_ptr(_j.get_ptr<njson::object_t*>()); }
            if (_j.is_string()) { return set_ptr(_j.get_ptr<njson::string_t*>()); }
            if (_j.is_binary()) { return set_ptr(_j.get_ptr<njson::binary_t*>()); }
            if (_j.is_boolean()) { return set_ptr(_j.get_ptr<njson::boolean_t*>()); }
            if (_j.is_number_integer()) { return set_ptr(_j.get_ptr<njson::number_integer_t*>()); }
            if (_j.is_number_unsigned()) { return set_ptr(_j.get_ptr<njson::number_unsigned_t*>()); }
            if (_j.is_number_float()) { return set_ptr(_j.get_ptr<njson::number_float_t*>()); }
            return set_nullptr();
        }

#define get(type_str) get_##type_str ()
        njson::object_t* get_object_ptr() { if (nullptr == ptr || object_ptr != type) { return nullptr; }return static_cast<njson::object_t*>(ptr); }
        njson::array_t* get_array_ptr() { if (nullptr == ptr || array_ptr != type) { return nullptr; }return static_cast<njson::array_t*>(ptr); }
        njson::string_t* get_string_ptr() { if (nullptr == ptr || string_ptr != type) { return nullptr; }return static_cast<njson::string_t*>(ptr); }
        njson::binary_t* get_binary_ptr() { if (nullptr == ptr || binary_ptr != type) { return nullptr; }return static_cast<njson::binary_t*>(ptr); }
        njson::boolean_t* get_boolean_ptr() { if (nullptr == ptr || boolean_ptr != type) { return nullptr; }return static_cast<njson::boolean_t*>(ptr); }
        njson::number_integer_t* get_integer_ptr() { if (nullptr == ptr || integer_ptr != type) { return nullptr; }return static_cast<njson::number_integer_t*>(ptr); }
        njson::number_unsigned_t* get_uinteger_ptr() { if (nullptr == ptr || uinteger_ptr != type) { return nullptr; }return static_cast<njson::number_unsigned_t*>(ptr); }
        njson::number_float_t* get_float_ptr() { if (nullptr == ptr || float_ptr != type) { return nullptr; }return static_cast<njson::number_float_t*>(ptr); }

        njson::object_t get_object() { if (nullptr == ptr || object_ptr != type) { return njson::object_t(); }return *(static_cast<njson::object_t*>(ptr)); }
        njson::array_t get_array() { if (nullptr == ptr || array_ptr != type) { return njson::array_t(); }return *(static_cast<njson::array_t*>(ptr)); }
        njson::string_t get_string() { if (nullptr == ptr || string_ptr != type) { return njson::string_t(); }return *(static_cast<njson::string_t*>(ptr)); }
        njson::binary_t get_binary() { if (nullptr == ptr || binary_ptr != type) { return njson::binary_t(); }return *(static_cast<njson::binary_t*>(ptr)); }
        njson::boolean_t get_boolean() { if (nullptr == ptr || boolean_ptr != type) { return njson::boolean_t(); }return *(static_cast<njson::boolean_t*>(ptr)); }
        njson::number_integer_t get_integer() { if (nullptr == ptr || integer_ptr != type) { return INT_MIN; }return *(static_cast<njson::number_integer_t*>(ptr)); }
        njson::number_unsigned_t get_uinteger() { if (nullptr == ptr || uinteger_ptr != type) { return UINT_MAX; }return *(static_cast<njson::number_unsigned_t*>(ptr)); }
        njson::number_float_t get_float() { if (nullptr == ptr || float_ptr != type) { return FLT_MIN; }return *(static_cast<njson::number_float_t*>(ptr)); }

        int get_val(njson::object_t&_val) { if (nullptr == ptr || object_ptr != type) { return RET_NG_TYPE;}_val= *(static_cast<njson::object_t*>(ptr));return RET_OK;}
        int get_val(njson::array_t&_val)  { if (nullptr == ptr || array_ptr != type) { return RET_NG_TYPE;}_val= *(static_cast<njson::array_t*>(ptr));return RET_OK;}
        int get_val(njson::string_t&_val) { if (nullptr == ptr || string_ptr != type) { return RET_NG_TYPE;}_val= *(static_cast<njson::string_t*>(ptr));return RET_OK;}
        int get_val(njson::binary_t&_val) { if (nullptr == ptr || binary_ptr != type) { return RET_NG_TYPE;}_val= *(static_cast<njson::binary_t*>(ptr));return RET_OK;}
        int get_val(njson::boolean_t&_val) { if (nullptr == ptr || boolean_ptr != type) { return RET_NG_TYPE;}_val= *(static_cast<njson::boolean_t*>(ptr));return RET_OK;}
        int get_val(njson::number_integer_t&_val) { if (nullptr == ptr || integer_ptr != type) { return RET_NG_TYPE;}_val= *(static_cast<njson::number_integer_t*>(ptr));return RET_OK;}
        int get_val(int &_val) { if (nullptr == ptr || integer_ptr != type) { return RET_NG_TYPE;}_val= *(static_cast<njson::number_integer_t*>(ptr));return RET_OK;}
        int get_val(njson::number_unsigned_t&_val) { if (nullptr == ptr || uinteger_ptr != type) { return RET_NG_TYPE;}_val= *(static_cast<njson::number_unsigned_t*>(ptr));return RET_OK;}
        int get_val(njson::number_float_t&_val) { if (nullptr == ptr || float_ptr != type) { return RET_NG_TYPE;}_val= *(static_cast<njson::number_float_t*>(ptr));return RET_OK;}

        int set_val(njson::object_t _val) { if (nullptr == ptr || object_ptr != type) { return RET_NG_ARG; }*(static_cast<njson::object_t*>(ptr)) = _val; return RET_OK; }
        int set_val(njson::array_t _val) { if (nullptr == ptr || array_ptr != type) { return RET_NG_ARG; }*(static_cast<njson::array_t*>(ptr)) = _val; return RET_OK; }
        int set_val(njson::string_t _val) {
            if (nullptr == ptr || string_ptr != type) {
                return RET_NG_ARG;
            }
            *(static_cast<njson::string_t*>(ptr)) = _val;
            return RET_OK;
        }
        int set_val(njson::binary_t _val) { if (nullptr == ptr || binary_ptr != type) { return RET_NG_ARG; }*(static_cast<njson::binary_t*>(ptr)) = _val; return RET_OK; }
        int set_val(njson::boolean_t _val) { if (nullptr == ptr || boolean_ptr != type) { return RET_NG_ARG; }*(static_cast<njson::boolean_t*>(ptr)) = _val; return RET_OK; }
        int set_val(njson::number_integer_t _val) { if (nullptr == ptr || integer_ptr != type) { return RET_NG_ARG; }*(static_cast<njson::number_integer_t*>(ptr)) = _val; return RET_OK; }
        int set_val(int _val) { if (nullptr == ptr || integer_ptr != type) { return RET_NG_ARG; }*(static_cast<njson::number_integer_t*>(ptr)) = _val; return RET_OK; }
        int set_val(njson::number_unsigned_t _val) { if (nullptr == ptr || uinteger_ptr != type) { return RET_NG_ARG; }*(static_cast<njson::number_unsigned_t*>(ptr)) = _val; return RET_OK; }
        int set_val(njson::number_float_t _val) { if (nullptr == ptr || float_ptr != type) { return RET_NG_ARG; }*(static_cast<njson::number_float_t*>(ptr)) = _val; return RET_OK; }
    };

    njson_data_ptr_container find_njson_value_obj_helper(njson::object_t* _obj, const std::string& _key,
        std::queue<njson_data_ptr_container> &_queue, int _index = -1) {
        njson::object_t::iterator cur_obj_ite = _obj->begin();
        njson::object_t::iterator cur_obj_ite_end = _obj->end();

        //check each element in cur json node(object or array)
        for (; cur_obj_ite != cur_obj_ite_end; ++cur_obj_ite) {
            //if cur element key equal _key
            if (_key == cur_obj_ite->first) {
                if (cur_obj_ite->second.is_array() && _index >= 0) {
                    njson::array_t* tary=cur_obj_ite->second.get_ptr<njson::array_t*>();
                    //out of array`s range
                    if(_index>=tary->size()) return njson_data_ptr_container();
                    return njson_data_ptr_container(cur_obj_ite->second[_index]);
                }
                return njson_data_ptr_container(cur_obj_ite->second);
            }
            //if cur element is array or object
            if (cur_obj_ite->second.is_array() ||
                cur_obj_ite->second.is_object()) {
                _queue.push(njson_data_ptr_container(cur_obj_ite->second));
            }
        }
        return njson_data_ptr_container();
    }

    void find_njson_value_ary_helper(njson::array_t* _ary,
        std::queue<njson_data_ptr_container> &_queue) {
        njson::array_t::iterator cur_ary_ite = _ary->begin();
        njson::array_t::iterator cur_ary_ite_end = _ary->end();
        for (; cur_ary_ite != cur_ary_ite_end; ++cur_ary_ite) {
            //if cur element is array or object
            if (cur_ary_ite->is_array() ||
                cur_ary_ite->is_object()) {
                _queue.push(njson_data_ptr_container(*cur_ary_ite));
            }
        }
    }

    njson_data_ptr_container find_njson_value_helper(njson_data_ptr_container& _ndpc,
                                                     const std::string& _key, int _index = -1){
        std::queue<njson_data_ptr_container> tqueue;
        njson_data_ptr_container tmp;
        njson_data_ptr_container cur;
        tqueue.push(_ndpc);
        if(array_ptr==_ndpc.type&&_key.empty()){
            njson::array_t* tary=_ndpc.get_array_ptr();
            if(_index<0||_index>=tary->size()) return njson_data_ptr_container();
            return njson_data_ptr_container((*tary)[_index]);
        }
        //BFS
        while (!tqueue.empty()) {
            cur = tqueue.front();
            tqueue.pop();
            if (object_ptr == cur.type) {
                //check each element`s type and do something in cur json object node,
                tmp = find_njson_value_obj_helper(cur.get(object_ptr), _key, tqueue, _index);
                if (void_ptr != tmp.type) {
                    return tmp;
                }
            }
            else if (array_ptr == cur.type) {
                //check each element`s type and do something  in cur json array node
                find_njson_value_ary_helper(cur.get(array_ptr), tqueue);
            }
        }
        //unfinded _key`s value;
        return njson_data_ptr_container();
    }
    njson_data_ptr_container find_njson_value(njson& _j, const std::string& _key, int _index = -1) {
        if (!(_j.is_array() || _j.is_object())) {//if not array or object return nullptr
            return njson_data_ptr_container();
        }
        njson_data_ptr_container ndpc(_j);
        return find_njson_value_helper(ndpc,_key,_index);
        if(false){
            std::queue<njson_data_ptr_container> tqueue;
            njson_data_ptr_container tmp;
            njson_data_ptr_container cur(_j);
            tqueue.push(cur);
            //BFS
            while (!tqueue.empty()) {
                cur = tqueue.front();
                tqueue.pop();
                if (object_ptr == cur.type) {
                    //check each element`s type and do something in cur json object node,
                    tmp = find_njson_value_obj_helper(cur.get(object_ptr), _key, tqueue, _index);
                    if (void_ptr != tmp.type) {
                        return tmp;
                    }
                }
                else if (array_ptr == cur.type) {
                    //check each element`s type and do something  in cur json array node
                    find_njson_value_ary_helper(cur.get(array_ptr), tqueue);
                }
            }
            //unfinded _key`s value;
            return njson_data_ptr_container();
        }
    }

    // <str?index> 为获取key为str的数组的第index个元素
    void parse_condition(const std::string _src,std::string &_dst,int &_index){
        _dst="";_index=-1;
        if(_src.empty())return;
        _dst=_src;
        _src.find_last_of('?');
        std::size_t idx=_src.find_last_of('?');
        if (idx!=std::string::npos){
            std::string index_str=_src.substr(idx+1);
            if(index_str.empty())return;
            for(auto ch:index_str){
                if(!(ch>='0'&&ch<='9')){
                    return;
                }
            }
            _index=std::atoi(index_str.c_str());
            _dst=_src.substr(0,idx);
        }
    }
    njson_data_ptr_container find_njson_value_ex(njson& _j, const std::string& _key, const conditions &_conditions,int _index = -1){
        njson_data_ptr_container tmp;
        njson_data_ptr_container cur(_j);
        std::string cur_condition="";
        int idx=-1;
        for(auto _condition:_conditions){
            parse_condition(_condition,cur_condition,idx);
            cur=find_njson_value_helper(cur,cur_condition,idx);
            if (void_ptr == cur.type) {
                return cur;
            }
        }
        return find_njson_value_helper(cur,_key,_index);
    }
protected:
    static Njson_Tool* s_njson_tool;
};

Njson_Tool* Njson_Tool::s_njson_tool=nullptr;

}
#endif // NJSON_TOOLS_H
