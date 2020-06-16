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

file(	GLOB_RECURSE
        source_image_to_stl
        src/*.cpp
)

file(	GLOB_RECURSE
        header_image_to_stl
        include/*.h
)

find_package( OpenCV REQUIRED )

# set the includes
include_directories(	include
                        ${OpenCV_INCLUDE_DIRS})

link_directories(	${OpenCV_LIBRARY_DIRS})


add_library(	image2stl SHARED
                ${source_image_to_stl})

#
target_link_libraries( 	image2stl
                        ${OpenCV_LIBS})


add_executable( im2stl apps/main.cpp)
#add_executable(2Drecognition exe/main.cpp)


#add_executable(TestContractor exe/test_contractor.cpp)

target_link_libraries(	im2stl
                        image2stl)
