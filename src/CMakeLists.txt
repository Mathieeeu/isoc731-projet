cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Graph)

set(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++")
set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc")

# Require C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable
add_executable(simple_graph simple_graph.cpp)
