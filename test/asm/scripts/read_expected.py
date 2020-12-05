import os

import constants


def _read_asm(line, lines):
    asm = ''

    while line and len(line) and line[0] == ' ':
        asm += line
        line = next(lines, None)

    return line, asm


def _split_func_and_arches(arches_to_keep, line):
    parts = line.split('#')
    func = parts[0].strip()

    arches = parts[1].strip().split(', ')
    if arches_to_keep:
        arches = [a for a in arches if a in arches_to_keep]
        if len(arches) == 0:
            return (None, None)
    return (func, arches)


def _read_functions(arches_to_keep, line, lines):
    res = []
    while line and len(line) != 0 and line[0] != ' ':
        func, arches = _split_func_and_arches(arches_to_keep, line)
        if func:
            res.append((func, arches))
        line = next(lines, None)

    return line, res


def _read_contents(arches_to_keep, lines):
    line = next(lines, None)

    res = {}

    while line:
        line, func_arches = _read_functions(arches_to_keep, line, lines)
        line, asm = _read_asm(line, lines)
        if len(asm) != 0 and len(func_arches) != 0:
            res[asm] = dict(func_arches)

    return res


def _read_file(file, arches_to_keep):
    with open(constants.EXPECTED_DIR.joinpath(file), 'r') as f:
        overload = file.split('.')[0]
        return (overload, _read_contents(arches_to_keep,
                                         (line for line in f.readlines() if len(line.strip()))))


def read_expected_results(arches=None):
  res = {}

  for file in os.listdir(constants.EXPECTED_DIR):
    overload, contents = _read_file(file, arches)
    res[overload] = contents

  return res
