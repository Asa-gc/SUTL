#ifndef JSONDOCUMENT_H
#define JSONDOCUMENT_H

#include <string>

class JsonDocument
{
public:
    JsonDocument();
    int set_str(const std::string &_data);
    std::string get_str(bool _flag=false);

    int get_value();

    int set_value();

    int add_value();

    int delete_member();

};

#endif // JSONDOCUMENT_H
