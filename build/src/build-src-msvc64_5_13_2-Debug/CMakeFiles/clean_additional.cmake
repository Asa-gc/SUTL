# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CPP_TOOLs_LOG_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CPP_TOOLs_LOG_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\SUTL_TEST_GV_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SUTL_TEST_GV_autogen.dir\\ParseCache.txt"
  "CPP_TOOLs_LOG_autogen"
  "SUTL_TEST_GV_autogen"
  )
endif()
