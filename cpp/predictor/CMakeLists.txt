add_library(Predictor OBJECT predictor.cpp)

target_include_directories(Predictor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../model)
