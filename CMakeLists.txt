cmake_minimum_required(VERSION 3.10)

set(CXX_STANDARD_REQUIRED 14)

project(fraction-class-cpp)

# fraction library

add_library(fraction STATIC 
    ${PROJECT_SOURCE_DIR}/fraction.h
    ${PROJECT_SOURCE_DIR}/fraction.cpp
)

# header-only fraction library

add_library(fraction_header_only INTERFACE)
target_include_directories(fraction_header_only INTERFACE .)

# demo targets

add_subdirectory(demo-polynomial)

add_executable(fraction_demo demo.cpp)
target_link_libraries(fraction_demo fraction_header_only)
