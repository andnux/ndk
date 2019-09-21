# Copyright 2014 Google Inc. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

{
  'target_defaults': {
    'target_conditions': [
      ['OS=="mac"', {
        'defines': ['HAVE_MACH_O_NLIST_H'],
      }],
      ['OS=="linux"', {
        'defines': ['HAVE_A_OUT_H'],
      }],
      ['OS!="android"', {'sources/': [['exclude', '(^|/)android/']]}],
      ['OS!="linux"', {'sources/': [['exclude', '(^|/)linux/']]}],
      ['OS!="mac"', {'sources/': [['exclude', '(^|/)mac/']]}],
      ['OS!="solaris"', {'sources/': [['exclude', '(^|/)solaris/']]}],
      ['OS!="win"', {'sources/': [['exclude', '(^|/)windows/']]}],
    ],
  },
  'targets': [
    {
      'target_name': 'common',
      'type': 'static_library',
      'sources': [
        'android/breakpad_getcontext.S',
        'android/include/elf.h',
        'android/include/link.h',
        'android/include/stab.h',
        'android/include/sys/procfs.h',
        'android/include/sys/signal.h',
        'android/include/sys/user.h',
        'android/include/ucontext.h',
        'android/testing/include/wchar.h',
        'android/testing/mkdtemp.h',
        'android/testing/pthread_fixes.h',
        'android/ucontext_constants.h',
        'basictypes.h',
        'byte_cursor.h',
        'convert_UTF.cc',
        'convert_UTF.h',
        'dwarf/bytereader-inl.h',
        'dwarf/bytereader.cc',
        'dwarf/bytereader.h',
        'dwarf/cfi_assembler.cc',
        'dwarf/cfi_assembler.h',
        'dwarf/dwarf2diehandler.cc',
        'dwarf/dwarf2diehandler.h',
        'dwarf/dwarf2enums.h',
        'dwarf/dwarf2reader.cc',
        'dwarf/dwarf2reader.h',
        'dwarf/dwarf2reader_test_common.h',
	'dwarf/elf_reader.cc',
	'dwarf/elf_reader.h',
        'dwarf/functioninfo.cc',
        'dwarf/functioninfo.h',
        'dwarf/line_state_machine.h',
        'dwarf/types.h',
        'dwarf_cfi_to_module.cc',
        'dwarf_cfi_to_module.h',
        'dwarf_cu_to_module.cc',
        'dwarf_cu_to_module.h',
        'dwarf_line_to_module.cc',
        'dwarf_line_to_module.h',
        'language.cc',
        'language.h',
        'linux/crc32.cc',
        'linux/crc32.h',
        'linux/dump_symbols.cc',
        'linux/dump_symbols.h',
        'linux/eintr_wrapper.h',
        'linux/elf_core_dump.cc',
        'linux/elf_core_dump.h',
        'linux/elf_gnu_compat.h',
        'linux/elf_symbols_to_module.cc',
        'linux/elf_symbols_to_module.h',
        'linux/elfutils-inl.h',
        'linux/elfutils.cc',
        'linux/elfutils.h',
        'linux/file_id.cc',
        'linux/file_id.h',
        'linux/google_crashdump_uploader.cc',
        'linux/google_crashdump_uploader.h',
        'linux/guid_creator.cc',
        'linux/guid_creator.h',
        'linux/http_upload.cc',
        'linux/http_upload.h',
        'linux/ignore_ret.h',
        'linux/libcurl_wrapper.cc',
        'linux/libcurl_wrapper.h',
        'linux/linux_libc_support.cc',
        'linux/linux_libc_support.h',
        'linux/memory_mapped_file.cc',
        'linux/memory_mapped_file.h',
        'linux/safe_readlink.cc',
        'linux/safe_readlink.h',
        'linux/synth_elf.cc',
        'linux/synth_elf.h',
        'long_string_dictionary.cc',
        'long_string_dictionary.h',
        'mac/arch_utilities.cc',
        'mac/arch_utilities.h',
        'mac/bootstrap_compat.cc',
        'mac/bootstrap_compat.h',
        'mac/byteswap.h',
        'mac/dump_syms.h',
        'mac/dump_syms.cc',
        'mac/file_id.cc',
        'mac/file_id.h',
        'mac/GTMDefines.h',
        'mac/GTMLogger.h',
        'mac/GTMLogger.m',
        'mac/HTTPMultipartUpload.h',
        'mac/HTTPMultipartUpload.m',
        'mac/MachIPC.h',
        'mac/MachIPC.mm',
        'mac/macho_id.cc',
        'mac/macho_id.h',
        'mac/macho_reader.cc',
        'mac/macho_reader.h',
        'mac/macho_utilities.cc',
        'mac/macho_utilities.h',
        'mac/macho_walker.cc',
        'mac/macho_walker.h',
        'mac/scoped_task_suspend-inl.h',
        'mac/string_utilities.cc',
        'mac/string_utilities.h',
        'mac/super_fat_arch.h',
        'md5.cc',
        'md5.h',
        'memory_allocator.h',
        'memory_range.h',
        'module.cc',
        'module.h',
        'scoped_ptr.h',
        'simple_string_dictionary.cc',
        'simple_string_dictionary.h',
        'solaris/dump_symbols.cc',
        'solaris/dump_symbols.h',
        'solaris/file_id.cc',
        'solaris/file_id.h',
        'solaris/guid_creator.cc',
        'solaris/guid_creator.h',
        'solaris/message_output.h',
        'stabs_reader.cc',
        'stabs_reader.h',
        'stabs_to_module.cc',
        'stabs_to_module.h',
        'string_conversion.cc',
        'string_conversion.h',
        'symbol_data.h',
        'test_assembler.cc',
        'test_assembler.h',
        'unordered.h',
        'using_std_string.h',
        'windows/common_windows.gyp',
        'windows/dia_util.cc',
        'windows/dia_util.h',
        'windows/guid_string.cc',
        'windows/guid_string.h',
        'windows/http_upload.cc',
        'windows/http_upload.h',
        'windows/omap.cc',
        'windows/omap.h',
        'windows/omap_internal.h',
        'windows/pdb_source_line_writer.cc',
        'windows/pdb_source_line_writer.h',
        'windows/string_utils-inl.h',
        'windows/string_utils.cc',
      ],
      'include_dirs': [
        '..',
      ],
    },
    {
      'target_name': 'common_unittests',
      'type': 'executable',
      'sources': [
        'android/breakpad_getcontext_unittest.cc',
        'byte_cursor_unittest.cc',
        'dwarf/bytereader_unittest.cc',
        'dwarf/dwarf2diehandler_unittest.cc',
        'dwarf/dwarf2reader_cfi_unittest.cc',
        'dwarf/dwarf2reader_die_unittest.cc',
        'dwarf_cfi_to_module_unittest.cc',
        'dwarf_cu_to_module_unittest.cc',
        'dwarf_line_to_module_unittest.cc',
        'linux/dump_symbols_unittest.cc',
        'linux/elf_core_dump_unittest.cc',
        'linux/elf_symbols_to_module_unittest.cc',
        'linux/file_id_unittest.cc',
        'linux/google_crashdump_uploader_test.cc',
        'linux/linux_libc_support_unittest.cc',
        'linux/memory_mapped_file_unittest.cc',
        'linux/safe_readlink_unittest.cc',
        'linux/synth_elf_unittest.cc',
        'linux/tests/auto_testfile.h',
        'linux/tests/crash_generator.cc',
        'linux/tests/crash_generator.h',
        'long_string_dictionary_unittest.cc',
        'mac/macho_reader_unittest.cc',
        'memory_allocator_unittest.cc',
        'memory_range_unittest.cc',
        'module_unittest.cc',
        'simple_string_dictionary_unittest.cc',
        'stabs_reader_unittest.cc',
        'stabs_to_module_unittest.cc',
        'string_conversion_unittest.cc',
        'test_assembler_unittest.cc',
        'tests/auto_tempdir.h',
        'tests/file_utils.cc',
        'tests/file_utils.h',
        'windows/omap_unittest.cc',
      ],
      'include_dirs': [
        '..',
      ],
      'dependencies': [
        'common',
        '../build/testing.gyp:gmock_main',
        '../build/testing.gyp:gmock',
        '../build/testing.gyp:gtest',
      ],
      'libraries': [
        '-ldl',
      ],
    },
  ],
}
