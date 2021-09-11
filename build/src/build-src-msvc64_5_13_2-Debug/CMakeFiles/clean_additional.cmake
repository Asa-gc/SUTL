# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CPP_TOOLs_JSON_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CPP_TOOLs_JSON_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\CPP_TOOLs_LOG_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CPP_TOOLs_LOG_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\QML_TOOLs_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QML_TOOLs_autogen.dir\\ParseCache.txt"
  "CPP_TOOLs_JSON_autogen"
  "CPP_TOOLs_LOG_autogen"
  "QML_TOOLs_autogen"
  )
endif()
