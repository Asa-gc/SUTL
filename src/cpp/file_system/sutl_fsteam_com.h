#ifndef SULT_FSTEAM_COM_H
#define SULT_FSTEAM_COM_H
#include <io.h>
#include <direct.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../sutl_heads.h"
namespace _sutl {
//check folder exist
inline bool check_folder_exist(const std::string & _folder)
{
    int ftyp = _access(_folder.c_str(), 0);
    if (0 == ftyp)
        return true;   // this is a directory!
    else
        return false;    // this is not a directory!
}

//creat folder, the folder`s parent path must be exsit
inline bool creat_folder(const std::string & _folderpath){
     return !mkdir(_folderpath.c_str());
}

inline std::vector<std::string> splict_str(const std::string & _str,const std::string &_symbol){
    std::vector<std::string> res;
    if(_str.empty())return res;
    std::string str=_str;
    size_t idx=0;
    do{
        idx=str.find(_symbol);
        res.emplace_back(str.substr(0,idx));
        str=str.substr(idx+1);
    }while(idx!=_str.npos);
    return res;
}

inline bool creat_path_helper(const std::string & _folderpath,const std::string &_symbol="/"){
    std::vector<std::string> folders=splict_str(_folderpath,_symbol);
    std::string tpath="";
    for(auto ite:folders){
        tpath+=ite;
        if(false==check_folder_exist(tpath)){
            if(false==creat_folder(tpath)){
                return false;
            }
        }
        tpath+=_symbol;
    }
    return true;
}

inline bool creat_path(const std::string & _folderpath){
    return creat_path_helper(_folderpath)?true:creat_path_helper(_folderpath,"\\");
}
inline bool creat_path_ex(const std::string & _folderpath,const std::string &_symbol){
    return creat_path_helper(_folderpath)?true:creat_path_helper(_folderpath,_symbol);
}

inline int read_img_data(const std::string &_filename,std::string&_dst){
    if(_filename.empty()){
        std::cerr<<"filename is empty"<<std::endl;
        return RET_NG_ARG;
    }
    std::fstream read(_filename,std::ios::in|std::ios::binary);
    if(false==read.is_open()){
        std::cerr<<"open one file Fail.filename: "<<_filename<<std::endl;
        return RET_NG_ARG;
    }
    read.seekg(0, read.end);
    int length = read.tellg();
    read.seekg(0, read.beg);
    char * buffer = new char[length];
    read.read(buffer, length);
    _dst=std::string(buffer,length);
    delete [] buffer;
    read.close();
    return RET_OK;
}

inline int write_img_data(const std::string &_filename,const std::string&_dst){
    if(_filename.empty()){
        std::cerr<<"filename is empty"<<std::endl;
        return RET_NG_ARG;
    }
    std::fstream write(_filename,std::ios::out|std::ios::binary|std::ios::trunc);
    if(false==write.is_open()){
        std::cerr<<"open one file Fail.filename: "<<_filename<<std::endl;
        return RET_NG_ARG;
    }
    std::cout<<"open one file successed.filename: "<<_filename<<std::endl;
    write<<_dst;
    write.close();
    return RET_OK;
}

inline int read_all_file_data(const std::string &_filename,std::string&_dst){
    if(_filename.empty()){
        std::cerr<<"filename is empty"<<std::endl;
        return RET_NG_ARG;
    }
    std::fstream read(_filename,std::ios::in);
    if(false==read.is_open()){
        std::cerr<<"open one file Fail.filename: "<<_filename<<std::endl;
        return RET_NG_ARG;
    }
    std::cout<<"open one file successed.filename: "<<_filename<<std::endl;
    std::stringstream buffer;
    buffer << read.rdbuf();
    _dst=buffer.str();
    read.close();
    return RET_OK;
}

inline int write_to_file(const std::string &_filename,const std::string&_data){
    if(_filename.empty()){
        std::cerr<<"_filename is empty"<<std::endl;
        return RET_NG_ARG;
    }
    std::fstream write(_filename,std::ios::out|std::ios::trunc);
    if(false==write.is_open()){
        std::cerr<<"open one file Fail.filename: "<<_filename<<std::endl;
        return RET_NG_ARG;
    }
    std::cout<<"open one file successed.filename: "<<_filename<<std::endl;
    write<<_data;
    write.close();
    return RET_OK;
}

inline int write_to_file_with_check_path(const std::string &_path,
                                         const std::string &_filename,
                                         const std::string&_data){
    if(_path.empty()){
        std::cerr<<"_path is empty"<<std::endl;
        return RET_NG_ARG;
    }
    if(false==check_folder_exist(_path)){
        std::cout<<"_path is not exist,now creat it! _path:"
                <<_path<<std::endl;
        if(false==creat_path(_path)){
            std::cerr<<"creat _path fail!!!"<<std::endl;
            return RET_NG_ARG;
        }
    }
    write_to_file(_path+"/"+_filename,_data);
}

inline bool check_folder_exist_ex(const std::string & _folder,bool _creat_if_miss=false,const std::string &_symbol="/"){
    int ftyp = _access(_folder.c_str(), 0);
    if (0 == ftyp){// this is a directory!
        return true;
    }
    return _creat_if_miss?creat_path_ex(_folder,_symbol):false;
}

}//_sutl

#endif // SULT_FSTEAM_COM_H
