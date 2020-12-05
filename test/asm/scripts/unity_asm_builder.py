#!/usr/bin/env python3.9
import os
import tempfile

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
        file = tempfile.NamedTemporaryFile(
            mode='w', suffix='.cc', delete=False)
        with file as unity:
            for s in sources:
                unity.write(f'#include "{s}"\n')

        res = None
        try:
            res = clean_up_asm(self._compiler(file.name))
        except:
            os.remove(file.name)
            raise

        os.remove(file.name)
        return (self._arch, res)
