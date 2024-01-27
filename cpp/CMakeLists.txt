cmake_minimum_required(VERSION 3.8)
project(e_machine_learning)

option(COMPILE_FOR_RPI "Compile for Raspberry Pi" OFF)
option(DEBUG "Debug mode" OFF)

set(CMAKE_CXX_STANDARD 20)

if(COMPILE_FOR_RPI)
    add_definitions(-DCOMPILE_FOR_RPI)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/home/pi/tensorflow")
elseif(DEBUG)
    add_definitions(-DDEBUG)
    if(APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/lib/python3.11/site-packages/numpy/core/include/ -I/usr/local/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/include/python3.11")
        include_directories(/usr/local/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/include/python3.11)  
    endif()

    if(UNIX AND NOT APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/lib/python3/dist-packages -I/usr/include/python3.11 -L/usr/bin/python3")
    endif()
endif()

add_subdirectory(audio_preprocessing)
add_subdirectory(audio_preprocessing/tools)
add_subdirectory(predictor)
add_subdirectory(model)

include_directories(/home/pi/tensorflow)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/audio_preprocessing)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/audio_preprocessing/tools)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/predictor)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/model)

add_executable(e_machine_learning.o main.cpp)

if(COMPILE_FOR_RPI)
    target_link_libraries(e_machine_learning.o AudioPreprocessing AuUtils FFTUtils Constants Predictor
                          /home/pi/machine_learning_embedded/projet/libtensorflow-lite.a -pthread -lrt -ldl)
elseif(DEBUG)
    find_package(Python3 COMPONENTS Development NumPy)
    target_include_directories(e_machine_learning.o PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
    target_link_libraries(e_machine_learning.o Python3::Python Python3::NumPy)
    target_link_libraries(e_machine_learning.o AudioPreprocessing AuUtils FFTUtils Constants Predictor)
else()
    target_link_libraries(e_machine_learning.o AudioPreprocessing AuUtils FFTUtils Constants Predictor)
endif()
