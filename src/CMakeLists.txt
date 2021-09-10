cmake_minimum_required(VERSION 3.5)

project(SUTL LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

########qml_tool#########
if(ANDROID)
    add_library(QML_TOOLs SHARED
      main.cpp
      qml.qrc
    )
else()
    add_executable(QML_TOOLs
      main_qml.cpp
      qml.qrc
    )
endif()
target_compile_definitions(QML_TOOLs
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QML_TOOLs
  PRIVATE Qt5::Core Qt5::Quick)


########cpp_tool#########

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

set(LOG_FILES cpp/Log/log_if.h
              cpp/Log/log_if.cpp
              cpp/Log/log_imp_log4cplus.h
              cpp/Log/log_imp_log4cplus.cpp
              cpp/Log/log_imp_glog.h
              cpp/Log/log_imp_glog.cpp
              )
if(ANDROID)
    add_library(CPP_TOOLs SHARED
      main.cpp
      qml.qrc
    )
else()
    add_executable(CPP_TOOLs
      main_cpp.cpp
      cpp/Qt/json/jsondocument.h
      cpp/Qt/json/jsondocument.cpp
      cpp/Qt/json/jsondocumentimp.h
      cpp/Qt/json/jsondocumentimp.cpp
      ${LOG_FILES}
      qml.qrc
    )
endif()
target_compile_definitions(CPP_TOOLs
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(CPP_TOOLs
  PRIVATE Qt5::Core Qt5::Quick ${LOG4CPLUS_LIBRARYFile} ${GLOG_LIBRARYFile}
  )
