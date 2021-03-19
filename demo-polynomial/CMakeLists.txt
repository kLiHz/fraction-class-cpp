cmake_minimum_required(VERSION 3.10)

project(Polynomial-Calculator)

include_directories(.)

add_executable( poly_mono_demo 
    demo.cpp 
    monomial.h 
    polynomial.h
    monomial.cpp 
    polynomial.cpp
)

target_link_libraries(poly_mono_demo fraction)

add_executable( poly3 
    main.cpp 
    monomial.h 
    polynomial.h
    monomial.cpp 
    polynomial.cpp
)

target_link_libraries(poly3 fraction)
