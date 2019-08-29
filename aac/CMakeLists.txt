# source code: git clone https://android.googlesource.com/platform/external/aac
cmake_minimum_required(VERSION 2.8)

set(SOURCE_DIR src/main/cpp)

file(GLOB CPP ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.c)
list(APPEND SOURCE_FILES ${CPP})

add_definitions(
        -fno-rtti
        -fno-exceptions)

foreach (subdir
        libAACdec libArithCoding libFDK
        libMpegTPEnc libSACdec libSBRdec
        libSYS libAACenc libDRCdec
        libMpegTPDec libPCMutils libSACenc
        libSBRenc)
    set(__inc_dir ${SOURCE_DIR}/${subdir}/include)
    include_directories(${__inc_dir})
    file(GLOB __src_files
            ${SOURCE_DIR}/${subdir}/src/*.cpp
            ${SOURCE_DIR}/${subdir}/src/*.h)
    list(APPEND SOURCE_FILES ${__src_files})
endforeach ()

add_library(aac SHARED ${SOURCE_FILES})
target_link_libraries(aac log)