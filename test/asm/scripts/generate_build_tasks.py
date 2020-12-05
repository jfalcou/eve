#!/usr/bin/env python3.9
import itertools
import pathlib
import os

import constants
from unity_asm_builder import UnityAsmBuilder


def _chunks(lst, n):
    for i in range(0, len(lst), n):
        yield lst[i:i + n]


def generate_build_tasks(arches=None,
                         sources=None,
                         unity_block_size=None):
    if not sources:
        sources = [s for s in os.listdir(
            constants.TEST_SOURCES) if s.endswith('cc')]

    sources = [
        str(constants.TEST_SOURCES.joinpath(s).resolve()) for s in sources]

    if not arches:
        arches = constants.ALL_ARCHES

    if not unity_block_size:
        unity_block_size = 40  # by default pack 40 files in one

    return itertools.product(
        [UnityAsmBuilder(arch) for arch in arches],
        _chunks(sources, unity_block_size)
    )
