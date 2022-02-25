#ifndef RETURN_VALUE_H
#define RETURN_VALUE_H
#define NG_START_IDX 100
#define NG_IDX(idx) NG_START_IDX+(idx)
//Self Use Tool Lib
namespace _sutl {
enum RET_V {
    RET_OK = 0,
    RET_OK_WAIT_TODO=RET_OK,
    RET_OK_PART,
    RET_OK_DONOTHING,

    RET_NG                          = NG_IDX(0),
    RET_NG_ARG                      = NG_IDX(1),
    RET_NG_INVOK                    = NG_IDX(2),
    RET_NG_UNLOGIN                  = NG_IDX(3),
    RET_NG_FUNC_UNFINDED            = NG_IDX(4),
    RET_NG_NULLPTR                  = NG_IDX(5),
    RET_NG_CATCH_EXCEPTION          = NG_IDX(6),
    RET_NG_UNCONNECTED              = NG_IDX(7),
    RET_NG_TYPE_UNDEFINED           = NG_IDX(8),
    RET_NG_EMPTY                    = NG_IDX(9),
    RET_NG_UNFINDED                 = NG_IDX(10),
    RET_NG_ADD                      = NG_IDX(11),
    RET_NG_TIMEOUT                  = NG_IDX(11),
    RET_NG_TYPE                     = NG_IDX(12),
};
}
#endif // RETURN_VALUE_H
