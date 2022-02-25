#ifndef SULT_MACRO_H
#define SULT_MACRO_H

//#include "../log/log_macro.h"
#define str2qstr(str) QString::fromStdString((str))

#define DEFINE_VAR_HELPER(_type,_val_name,_empty)\
private:\
    _type##_empty _empty##_val_name = _type##_empty ();\
public:\
    _type##_empty get_##_val_name(){return _empty##_val_name;}\
    void set_##_val_name(const _type##_empty &_val){_empty##_val_name=_val;}

#define DEFINE_VAR(_type,_val_name) DEFINE_VAR_HELPER(_type,_val_name, )

#endif // SULT_MACRO_H
