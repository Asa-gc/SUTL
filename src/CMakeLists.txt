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
#    cpp/Log/log_imp_log4cplus.cpp
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

########cpp_tool_JSON#########
set(JSON_DIR "${CMAKE_CURRENT_LIST_DIR}/cpp/Json")
set(JSON_FILES
    cpp/Json/jsondocument.h
    cpp/Json/jsondocument.cpp
    cpp/Json/jsondocumentImp.h
    cpp/Json/nlohmann/jsondocumentImp.cpp
    cpp/Json/nlohmann/json.hpp
    )
add_executable(CPP_TOOLs_JSON
    ${JSON_DIR}/main.cpp
    ${JSON_FILES}
    qml.qrc
)
target_compile_definitions(CPP_TOOLs_JSON
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(CPP_TOOLs_JSON
  PRIVATE Qt5::Core Qt5::Quick ${LOG4CPLUS_LIBRARYFile} ${GLOG_LIBRARYFile}
  )
