cmake_minimum_required(VERSION 3.4.1)
include_directories(src/main/cpp/common/android/include src/main/cpp)
enable_language(ASM)
add_library(
        breakpad
        SHARED
        src/main/cpp/client/linux/crash_generation/crash_generation_client.cc
        src/main/cpp/client/linux/dump_writer_common/thread_info.cc
        src/main/cpp/client/linux/dump_writer_common/ucontext_reader.cc
        src/main/cpp/client/linux/handler/exception_handler.cc
        src/main/cpp/client/linux/handler/minidump_descriptor.cc
        src/main/cpp/client/linux/log/log.cc
        src/main/cpp/client/linux/microdump_writer/microdump_writer.cc
        src/main/cpp/client/linux/minidump_writer/linux_dumper.cc
        src/main/cpp/client/linux/minidump_writer/linux_ptrace_dumper.cc
        src/main/cpp/client/linux/minidump_writer/minidump_writer.cc
        src/main/cpp/client/minidump_file_writer.cc
        src/main/cpp/common/android/breakpad_getcontext.S
        src/main/cpp/common/convert_UTF.cc
        src/main/cpp/common/md5.cc
        src/main/cpp/common/string_conversion.cc
        src/main/cpp/common/linux/elfutils.cc
        src/main/cpp/common/linux/file_id.cc
        src/main/cpp/common/linux/guid_creator.cc
        src/main/cpp/common/linux/linux_libc_support.cc
        src/main/cpp/common/linux/memory_mapped_file.cc
        src/main/cpp/common/linux/safe_readlink.cc
        src/main/cpp/native-lib.cpp)
find_library(log-lib log)
target_link_libraries(breakpad ${log-lib})