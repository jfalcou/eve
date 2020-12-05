#!/usr/bin/env python3.9

import re
import subprocess
import sys


def clean_up_whitespace(lines):
    for line in lines:
        if len(line.strip()) == 0:
            continue
        yield line.replace('\t', '    ')


def clean_up_comments(lines):
    for line in lines:
        comment_start = line.find('#')
        if comment_start == -1:
            yield line
            continue

        line = line[:comment_start]
        if len(line.strip()) != 0:
            yield line


def clean_up_directives(lines):
    for line in lines:
        if line.strip()[0] == '.':
            continue
        yield line


def clean_up_GLOBAL_section(lines):
    for line in lines:
        if line.startswith('_GLOBAL_'):
            break
        yield line


def _split_by_function(lines):
    asm_by_function = {}

    current_function = ''
    for line in lines:
        if line[0] != ' ':
            current_function = line.split('(')[0]
            if current_function not in asm_by_function:
                asm_by_function[current_function] = ''
            else:
                asm_by_function[current_function] += '\n'
        asm_by_function[current_function] += line
        asm_by_function[current_function] += '\n'

    return asm_by_function


def clean_up_asm(asm):
    lines = asm.split('\n')
    lines = clean_up_whitespace(lines)
    lines = clean_up_comments(lines)
    lines = clean_up_directives(lines)
    lines = clean_up_GLOBAL_section(lines)
    return _split_by_function(lines)
