cmake_minimum_required(VERSION 3.10)

set(CXX_STANDARD_REQUIRED 14)

project(fraction-class-cpp)

include_directories(.)

add_library(fraction STATIC ${PROJECT_SOURCE_DIR}/fraction.cpp)

add_subdirectory(demo-polynomial)

add_executable(fraction_demo demo.cpp)
