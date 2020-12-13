cmake_minimum_required(VERSION 3.5)

project(lab7)

add_executable(lab7 main.cpp)

set_property(TARGET lab7 PROPERTY CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
