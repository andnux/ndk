cmake_minimum_required(VERSION 3.2)

set(CMAKE_ANDROID_ARM_MODE true)
set(ANDROID_CPP_FEATURES rtti exceptions)
set(ANDROID_STL c++_static)
set(CMAKE_C_FLAGS -fvisibility=hidden -fdata-sections -ffunction-sections)

INCLUDE_DIRECTORIES(src/main/cpp/soundtouch/include
        src/main/cpp
        src/main/cpp/soundtouch)
file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/main/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main/cpp/soundtouch/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main/cpp/*.c)
add_library(soundtouch
        SHARED
        ${SRC})
target_link_libraries(soundtouch log android)