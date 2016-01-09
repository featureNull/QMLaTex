cmake_minimum_required(VERSION 3.0.2)

project(qmlatex)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

add_subdirectory(src)
