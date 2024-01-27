add_library(AuUtils OBJECT au_utils.cpp)
add_library(Constants OBJECT constants.h)
add_library(FFTUtils OBJECT fft_utils.cpp)

if(DEBUG)
    add_library(Plot OBJECT plot.h)
    add_library(MatplotlibCpp OBJECT matplotlibcpp.h)
endif()