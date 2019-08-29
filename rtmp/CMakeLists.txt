cmake_minimum_required(VERSION 3.2)

include_directories(libs/include src/main/cpp/rtmp src/main/cpp)

file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/main/cpp/rtmp/*.c
        ${CMAKE_SOURCE_DIR}/src/main/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main/cpp/*.c)
add_library(rtmp SHARED ${SRC})

set(ABI ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI})
target_link_libraries(rtmp log z ${ABI}/libssl.a ${ABI}/libcrypto.a)