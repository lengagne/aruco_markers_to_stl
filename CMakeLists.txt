cmake_minimum_required (VERSION 2.8)
enable_language(CXX)
project(image_to_stl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -msse2 -fPIC")

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(PROJECT_CONTACT lengagne@gmail.com)


foreach(p LIB INCLUDE)
        set(var CMAKE_INSTALL_${p}DIR)
        if(NOT IS_ABSOLUTE "${${var}}")
                set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
        endif()
endforeach()


# set the includes
include_directories(	include )



add_executable( im2stl apps/main.cpp)
