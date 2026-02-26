cmake_minimum_required(VERSION 3.16)
project(oop_lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_library(headers variable_descriptor.hpp vector_descriptor.hpp matrix_descriptor.hpp table.hpp vector.hpp headers.cpp)
add_library(identifier identifier.hpp identifier.cpp)
add_library(input input.hpp input.cpp)
add_library(threads threads.hpp threads.cpp)
link_libraries(headers identifier input threads)
add_executable(test main.cpp)

