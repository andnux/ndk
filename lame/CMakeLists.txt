cmake_minimum_required(VERSION 2.8.2)

include_directories(src/main/cpp/lame src/main/cpp)

set(LAME src/main/cpp/lame)

set(CMAKE_C_FLAGS "-DSTDC_HEADERS")

file(GLOB SRC src/main/cpp/*.c
        src/main/cpp/lame/vector/*.c
        src/main/cpp/lame/*.c )

add_library(lame SHARED ${SRC})

target_link_libraries(lame log)
