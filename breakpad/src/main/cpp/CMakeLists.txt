cmake_minimum_required(VERSION 3.4.1)
include_directories(common/android/include .)
enable_language(ASM)
add_library(
        breakpad
        SHARED
        client/linux/crash_generation/crash_generation_client.cc
        client/linux/dump_writer_common/thread_info.cc
        client/linux/dump_writer_common/ucontext_reader.cc
        client/linux/handler/exception_handler.cc
        client/linux/handler/minidump_descriptor.cc
        client/linux/log/log.cc
        client/linux/microdump_writer/microdump_writer.cc
        client/linux/minidump_writer/linux_dumper.cc
        client/linux/minidump_writer/linux_ptrace_dumper.cc
        client/linux/minidump_writer/minidump_writer.cc
        client/minidump_file_writer.cc
        common/android/breakpad_getcontext.S
        common/convert_UTF.cc
        common/md5.cc
        common/string_conversion.cc
        common/linux/elfutils.cc
        common/linux/file_id.cc
        common/linux/guid_creator.cc
        common/linux/linux_libc_support.cc
        common/linux/memory_mapped_file.cc
        common/linux/safe_readlink.cc
        native-lib.cpp)
find_library(log-lib log)
target_link_libraries(breakpad ${log-lib})