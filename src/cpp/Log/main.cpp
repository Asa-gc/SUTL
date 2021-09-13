#include <iostream>
#include "logapi.h"
using namespace std;
int main(int argc, char *argv[])
{
    LOG_TRACE3(__FUNCTION__);
    LOG_ERROR("this error");
    cout<<"Hallo World!"<<endl;
    return 1;
}
