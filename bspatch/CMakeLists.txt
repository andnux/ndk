cmake_minimum_required(VERSION 3.2)

include_directories(src/main/cpp)

file(GLOB SRC src/main/cpp/*.c)

add_library(bspatch SHARED ${SRC})

target_link_libraries(bspatch log)
