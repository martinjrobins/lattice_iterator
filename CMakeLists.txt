cmake_minimum_required(VERSION 3.1.0)
project(Lattice)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cxxtest/build_tools/cmake/"
                      "${CMAKE_SOURCE_DIR}/cmake"
                        ${CMAKE_MODULE_PATH})


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

#export compiler flags for code completion engines
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

set(Lattice_INCLUDES "")
set(Lattice_LIBRARIES "")

include_directories(src)
include_directories(SYSTEM ${Lattice_INCLUDES})

enable_testing()
add_subdirectory(tests)

