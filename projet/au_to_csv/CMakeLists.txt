# CMakeLists.txt principal
cmake_minimum_required(VERSION 3.8)
project(machine_learning)

set(CMAKE_CXX_STANDARD 20)

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/lib/python3.11/site-packages/numpy/core/include/ -I/usr/local/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/include/python3.11")
    include_directories(/usr/local/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/include/python3.11)  
endif()

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/lib/python3/dist-packages -I/usr/include/python3.11 -L/usr/bin/python3")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

add_subdirectory(src)
add_subdirectory(tools)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools)

add_executable(machine_learning.o main.cpp)

find_package(Python3 COMPONENTS Development NumPy)
target_include_directories(machine_learning.o PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
target_link_libraries(machine_learning.o Python3::Python Python3::NumPy)
target_link_libraries(machine_learning.o AudioPreprocessing AuUtils FFTUtils Constants)
