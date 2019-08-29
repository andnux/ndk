cmake_minimum_required(VERSION 3.2)

include_directories(libs/include  src/main/cpp)

file(GLOB SRC
        ${CMAKE_SOURCE_DIR}/src/main/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main/cpp/*.c)

add_library(h264 SHARED ${SRC})


add_library(x264
        SHARED
        IMPORTED)
set_target_properties(x264
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libx264.so)

target_link_libraries(h264 log x264)

#set(ABI ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI})
#target_link_libraries(x264 log ${ABI}/x264.a)