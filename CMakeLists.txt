cmake_minimum_required(VERSION 3.10)

set(CXX_STANDARD_REQUIRED 14)

project(fraction-class-cpp)

include_directories(.)

add_library(fraction STATIC ${PROJECT_SOURCE_DIR}/fraction.cpp)

# Polynomial Calculator

add_subdirectory(demo-polynomial)

# Fraction Demo

add_executable(fraction_demo demo.cpp)

# Fraction CalCulator

add_subdirectory(fraction-calculator)
