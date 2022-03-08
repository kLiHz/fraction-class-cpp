cmake_minimum_required(VERSION 3.10)

set(CXX_STANDARD_REQUIRED 14)

project(Polynomial)

# poly-mono file glob

add_library(poly_mono STATIC monomial.h monomial.cpp polynomial.h polynomial.cpp)
target_link_libraries(poly_mono fraction_header_only)

# poly-mono demo

add_executable(poly_mono_demo demo.cpp)
target_link_libraries(poly_mono_demo poly_mono fraction_header_only)

# Polynomial Calculator

add_executable(poly3 main.cpp)
target_link_libraries(poly3 poly_mono fraction_header_only)
