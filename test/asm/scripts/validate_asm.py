import argparse
import pathlib

import constants

from compilation_driver import run_compilation, compilation_arguments
from read_expected import read_expected_results


def parse_options():
    parser = argparse.ArgumentParser(
        description='''
Part of assembly approval testing.
Tests generated assembly against the one in 'test/asm/expected'.
You can optionally supply specific source instead of all.
You can also specify architectures (by default will compile all availiable ones).
Compiler used: $CXX
Extra options can be passed through: $CXX_OPTIONS
''',
        formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('--missing_is_ok', required=False,
                        action='store_true')
    compilation_arguments(parser)
    return parser.parse_args()


def invert_overload(overload):
    res = {}
    for asm, func_arches in overload.items():
        for func, arches in func_arches.items():
            for arch in arches:
                res[f'{func} for {arch}'] = asm
    return res


def _overload_mismatch(expected, actual, missing_is_ok):
    expected = invert_overload(expected)
    actual = invert_overload(actual)

    if not missing_is_ok:
        for f_a in expected:
            if not f_a in actual:
                return f'{f_a} was not generated!'

    for f_a in actual:
        if not f_a in expected:
            return f'{f_a} has no expected!'

        if expected[f_a] != actual[f_a]:
            return f'Mismatch for {f_a}:\nExpected:\n{expected[f_a]}\nActual:\n{actual[f_a]}'

    return None


def _compare(expected, actual, missing_is_ok):
    if expected == actual:
        return None

    if not missing_is_ok:
        for overload in expected.keys():
            if not overload in actual:
                return f'{overload} was not generated!'

    for overload in actual.keys():
        if not overload in expected:
            return f'{overload} has no expected!'

        if expected[overload] == actual[overload]:
            continue

        return _overload_mismatch(expected[overload], actual[overload], missing_is_ok)


def main():
    options = parse_options()
    actual = run_compilation(options)
    expected = read_expected_results(options.arches)
    test = _compare(expected, actual, options.missing_is_ok)
    if not test:
        exit(0)
    print('\n\nFailure!!!===========\n')
    print(test)
    exit(1)


if __name__ == '__main__':
    main()
