#ifndef SUTL_REGISTER_H
#define SUTL_REGISTER_H
#include <map>
#include <string>

namespace _sutl {
class Sutl_Base;
class Sutl_Register_Manager;

typedef Sutl_Base* (*get_instance_func)(const std::map<std::string,std::string>&_arg2);
class Sutl_Register
{
public:

    static Sutl_Register *get_instance();
    static void add_regist_list_manager(const std::string &_manager_id);
    static void remove_regist_list_manager(const std::string &_manager_id);
    static Sutl_Register_Manager *get_regist_list_manager(const std::string &_manager_id);

    static void register_instance(const std::string& _class_id,
                                  get_instance_func _instanceFuc,
                                  const std::string &_manager_id="");

    static Sutl_Base *get_Class_instance(const std::string& _class_id,
                                         const std::map<std::string,std::string>&_arg
                                         =std::map<std::string,std::string>(),
                                         const std::string &_manager_id="");
protected:
    Sutl_Register();

    static Sutl_Register *s_register;
    static std::map<std::string,Sutl_Register_Manager> m_regist_list_manager;
};

class Sutl_Register_Manager
{
public:
    Sutl_Register_Manager(){}
    Sutl_Register_Manager(const std::string&_name):m_name(_name){

    }

protected:
    void register_instance(const std::string& _class_id,
                                  get_instance_func _instanceFuc,bool _replace=true);

    Sutl_Base *get_Class_instance(const std::string& _class_id,
                                  const std::map<std::string,std::string>&_arg
                                  =std::map<std::string,std::string>());

    get_instance_func get_one_instace_func(const std::string&_class_id);

    std::string get_name(){return m_name;}
    void set_name(const std::string&_name){m_name=_name;}

protected:
    std::map<std::string,get_instance_func> m_registList;
    std::string m_name="";
    friend class Sutl_Register;
};
}
#endif // SUTL_REGISTER_H
