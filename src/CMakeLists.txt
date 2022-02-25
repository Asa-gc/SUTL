cmake_minimum_required(VERSION 3.5)

project(SUTL LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

include_directories("${CMAKE_CURRENT_LIST_DIR}/cpp")

set(GTEST_DIR "${CMAKE_CURRENT_LIST_DIR}/3rd/gtest")
include_directories("${GTEST_DIR}/include")
add_library(gtest::gtest SHARED IMPORTED)
set_property(TARGET gtest::gtest PROPERTY IMPORTED_IMPLIB_RELEASE "${GTEST_DIR}/lib/${CMAKE_BUILD_TYPE}/gtest.lib")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_LOCATION_RELEASE "${GTEST_DIR}/bin/${CMAKE_BUILD_TYPE}/gtest.dll")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_IMPLIB_RELWITHDEBINFO "${GTEST_DIR}/lib/${CMAKE_BUILD_TYPE}/gtest.lib")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_LOCATION_RELWITHDEBINFO "${GTEST_DIR}/bin/${CMAKE_BUILD_TYPE}/gtest.dll")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_IMPLIB_DEBUG "${GTEST_DIR}/lib/${CMAKE_BUILD_TYPE}/gtestd.lib")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_LOCATION_DEBUG "${GTEST_DIR}/bin/${CMAKE_BUILD_TYPE}/gtestd.dll")
########cpp_tool_Log#########

set(LOG_DIR "${CMAKE_CURRENT_LIST_DIR}/cpp/Log")

set(LOG4CPLUS_ROOT "${CMAKE_CURRENT_LIST_DIR}/3rd/Log/log4cplus")
set(LOG4CPLUS_INCLUDEDIR "${LOG4CPLUS_ROOT}/include")

set(GLOG_ROOT "${CMAKE_CURRENT_LIST_DIR}/3rd/Log/glog")
set(GLOG_INCLUDEDIR "${GLOG_ROOT}/include")

if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(LOG4CPLUS_LIBRARYFile "${LOG4CPLUS_ROOT}/lib/log4cplus.lib")
    set(GLOG_LIBRARYFile "${GLOG_ROOT}/lib/glogd.lib")
else()
    set(LOG4CPLUS_LIBRARYFile "${LOG4CPLUS_ROOT}/lib/log4cplusD.lib")
    set(GLOG_LIBRARYFile "${GLOG_ROOT}/lib/glogd.lib")
endif()

include_directories(${LOG4CPLUS_INCLUDEDIR})
include_directories(${GLOG_INCLUDEDIR})

set(LOG_FILES
    cpp/Log/log_if.h
    cpp/Log/log_if.cpp
    cpp/Log/logapi.h
    cpp/Log/log_imp_log4cplus.h
    cpp/Log/log_imp_log4cplus.cpp
    cpp/Log/log_imp_glog.h
    cpp/Log/log_imp_glog.cpp
    )

add_executable(CPP_TOOLs_LOG
  ${LOG_DIR}/main.cpp
  ${LOG_FILES}

  qml.qrc
)
target_compile_definitions(CPP_TOOLs_LOG
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(CPP_TOOLs_LOG
  PRIVATE Qt5::Core Qt5::Quick ${LOG4CPLUS_LIBRARYFile} ${GLOG_LIBRARYFile}
  )

########SUTL_CORE#########


set(CORE_DIR ${CMAKE_CURRENT_LIST_DIR}/cpp/core)
set(CORE_FILES
    ${CORE_DIR}/sutl_register.cpp
    ${CORE_DIR}/sutl_register.h
    ${CORE_DIR}/sutl_base.cpp
    ${CORE_DIR}/sutl_base.h
    )
set(UNIT_DIR ${CMAKE_CURRENT_LIST_DIR}/cpp/unit)
set(UNIT_FILES
    ${UNIT_DIR}/sult_heads.h
    ${UNIT_DIR}/return_value.h
    )

#add_executable(SUTL_CORE
#    ${CORE_DIR}/main.cpp
#    ${GENERALVALUE_FILES}
#    ${CORE_FILES}
#    ${UNIT_FILES}
#)
#target_compile_definitions(SUTL_CORE
#  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
#target_link_libraries(SUTL_CORE
#  PRIVATE Qt5::Core Qt5::Quick
#  )




########SUTL_TEST_GV#########
set(GENERALVALUE_DIR ${CMAKE_CURRENT_LIST_DIR}/cpp/GeneralValue)
set(GENERALVALUE_FILES
    ${GENERALVALUE_DIR}/general_value.h
    ${GENERALVALUE_DIR}/general_value.cpp
    )

set(TEST_GV_DIR ${CMAKE_CURRENT_LIST_DIR}/cpp/test/gv)

add_executable(SUTL_TEST_GV
    ${TEST_GV_DIR}/main.cpp
    ${UNIT_FILES}
    ${GENERALVALUE_FILES}
)

target_compile_definitions(SUTL_TEST_GV
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(SUTL_TEST_GV
  PRIVATE Qt5::Core Qt5::Quick gtest::gtest
)
