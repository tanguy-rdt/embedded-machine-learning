add_library(Predictor OBJECT predictor.cpp)
add_library(Common OBJECT common.h)

target_include_directories(Predictor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../model)
