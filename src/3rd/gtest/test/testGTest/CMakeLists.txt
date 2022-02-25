cmake_minimum_required(VERSION 3.5)

project(testGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GTEST_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")
include_directories("${GTEST_DIR}/include")
add_library(gtest::gtest SHARED IMPORTED)
set_property(TARGET gtest::gtest PROPERTY IMPORTED_IMPLIB_RELEASE "${GTEST_DIR}/lib/${CMAKE_BUILD_TYPE}/gtest.lib")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_LOCATION_RELEASE "${GTEST_DIR}/bin/${CMAKE_BUILD_TYPE}/gtest.dll")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_IMPLIB_RELWITHDEBINFO "${GTEST_DIR}/lib/${CMAKE_BUILD_TYPE}/gtest.lib")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_LOCATION_RELWITHDEBINFO "${GTEST_DIR}/bin/${CMAKE_BUILD_TYPE}/gtest.dll")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_IMPLIB_DEBUG "${GTEST_DIR}/lib/${CMAKE_BUILD_TYPE}/gtestd.lib")
set_property(TARGET gtest::gtest PROPERTY IMPORTED_LOCATION_DEBUG "${GTEST_DIR}/bin/${CMAKE_BUILD_TYPE}/gtestd.dll")

add_executable(testGTest main.cpp)
target_link_libraries(testGTest
  PRIVATE gtest::gtest
)
