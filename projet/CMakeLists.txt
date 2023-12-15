# CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(machine_learning)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(machine_learning.o main.cpp)


