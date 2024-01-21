# CMakeLists.txt principal
cmake_minimum_required(VERSION 3.8)
project(e_machine_learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/home/pi/tensorflow")

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
target_link_libraries(e_machine_learning.o AudioPreprocessing AuUtils FFTUtils Constants Predictor
                    /home/pi/machine_learning_embedded/projet/libtensorflow-lite.a -pthread -lrt -ldl)
