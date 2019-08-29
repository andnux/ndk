cmake_minimum_required(VERSION 2.8.2)

include_directories(libs/include src/main/cpp)

file(GLOB SRC src/main/cpp/*.cpp
              src/main/cpp/*.c
              src/main/jni/*.c
              src/main/jni/*.cpp)

add_library(fmods SHARED ${SRC})

add_library(fmod
        SHARED
        IMPORTED)
set_target_properties(fmod
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libfmod.so)

add_library(fmodL
        SHARED
        IMPORTED)
set_target_properties(fmodL
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libfmodL.so)


target_link_libraries(fmods log fmodL fmod)

