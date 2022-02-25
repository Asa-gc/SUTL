#include "sutl_register.h"

namespace _sutl {
Sutl_Register *Sutl_Register::s_register=nullptr;
Sutl_Register::Sutl_Register()
{

}

Sutl_Register *Sutl_Register::get_instance()
{
    if(nullptr==s_register){
        s_register=new Sutl_Register;
        s_register->add_regist_list_manager("global");
    }
    return s_register;
}

void Sutl_Register::add_regist_list_manager(const std::string &_manager_id)
{
    if(m_regist_list_manager.find(_manager_id)!=m_regist_list_manager.end()){
        m_regist_list_manager[_manager_id]=Sutl_Register_Manager(_manager_id);
    }
}

void Sutl_Register::remove_regist_list_manager(const std::string &_manager_id)
{
    if(m_regist_list_manager.find(_manager_id)!=m_regist_list_manager.end()){
        m_regist_list_manager.erase(_manager_id);
    }
}

void Sutl_Register::register_instance(const std::string &_class_id,
                                      get_instance_func _instanceFuc,
                                      const std::string &_manager_id)
{
    std::string manager_id=_manager_id;
    if(manager_id.empty()){
        manager_id="global";
    }
    Sutl_Register_Manager *srm=get_regist_list_manager(manager_id);
    if(nullptr==srm){
        add_regist_list_manager(manager_id);
        srm=get_regist_list_manager(manager_id);
    }
    srm->register_instance(_class_id,_instanceFuc);
}

Sutl_Base *Sutl_Register::get_Class_instance(const std::string &_class_id,
                                             const std::map<std::string, std::string> &_arg,
                                             const std::string &_manager_id)
{

    std::string manager_id=_manager_id;
    if(manager_id.empty()){
        manager_id="global";
    }
    Sutl_Register_Manager *srm=get_regist_list_manager(manager_id);
    if(nullptr==srm){
        return nullptr;
    }
    return  srm->get_Class_instance(_class_id,_arg);
}

Sutl_Register_Manager *Sutl_Register::get_regist_list_manager(const std::string &_manager_id)
{
    if(m_regist_list_manager.find(_manager_id)!=m_regist_list_manager.end()){
        return &m_regist_list_manager[_manager_id];
    }
    return  nullptr;
}

void Sutl_Register_Manager::register_instance(const std::string &_class_id,
                                              get_instance_func _instanceFuc,
                                              bool _replace)
{
    if(_replace){
        m_registList[_class_id]=_instanceFuc;
        return;
    }
    if(m_registList.find(_class_id)==m_registList.end()){
        m_registList[_class_id]=_instanceFuc;
    }
}

Sutl_Base *Sutl_Register_Manager::get_Class_instance(const std::string &_class_id,
                                                     const std::map<std::string,
                                                     std::string> &_arg)
{
    get_instance_func func=this->get_one_instace_func(_class_id);
    if(nullptr==func){
        return nullptr;
    }
    return func(_arg);
}

get_instance_func Sutl_Register_Manager::get_one_instace_func(const std::string &_class_id)
{
    if(m_registList.end()==m_registList.find(_class_id)){
        return nullptr;
    }
    return m_registList[_class_id];
}
}
