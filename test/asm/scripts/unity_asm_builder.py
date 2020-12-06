#!/usr/bin/env python3.9
import os

from compiler import Compiler
from clean_up_asm import clean_up_asm


class UnityAsmBuilder:
    def __init__(self, arch):
        self._arch = arch
        self._compiler = Compiler(arch)

    def __repr__(self):
        return f'unity_builder({self._arch})'

    def __str__(self):
        return self.__repr__()

    def __call__(self, sources):
        source = ''.join((f'#include "{s}"\n' for s in sources))
        return (self._arch, clean_up_asm(self._compiler(source)))
