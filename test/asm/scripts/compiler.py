#!/usr/bin/env python3.9

import os
import enum
import subprocess
import constants

CXX = os.environ['CXX']
CXX_FLAGS = os.environ.get('CXX_FLAGS', '')

BASIC_FLAGS = [
    '--std=c++20',
    CXX_FLAGS,
    '-O3',
    '-Wall',
    '-Werror',
    '-DEVE_DISABLE_ASSERTS',
    '-o /dev/stdout',
    '-S',
    '-mllvm',
    '--x86-asm-syntax=intel',
    '-x c++ -- - '
]

ARCH_TO_COMMAND = {
    'sse2': '',
    'sse3': '-msse3',
    'ssse3': '-msse3',
    'sse4': '-msse4',
    'avx': '-mavx',
    'avx2': '-mavx2',
    # 'neon64'
    # 'neon128'
}


class Compiler:
    def __init__(self, arch):
        self._command = \
            f'{CXX} {ARCH_TO_COMMAND[arch]} ' \
            f'-I {constants.EVE_INCLUDE} '    \
            f'-I {constants.TEST_SOURCES} '   \
            f'{" ".join(BASIC_FLAGS)}'
        print(f'Initialized compiler: {self._command}')

    def __call__(self, code):
        compile_command =  f'echo \'{code}\' | {self._command} | c++filt'
        return subprocess.check_output(compile_command, shell=True, encoding='ascii')
