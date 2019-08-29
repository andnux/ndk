cmake_minimum_required(VERSION 3.2)
INCLUDE_DIRECTORIES(src/main/cpp/yuv/include src/main/cpp)
file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/main/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main/cpp/yuv/*.cc
        ${CMAKE_SOURCE_DIR}/src/main/cpp/*.c)
add_library(yuv
        SHARED
        ${SRC})
target_link_libraries(yuv log)