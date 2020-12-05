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

def _split_by_function(file):
  cur_function = ''
  for line in file.split('\n'):
    if len(line) == 0:
      continue

    if line[0] != ' ':
      if len(cur_function):
        yield cur_function
      cur_function = ''
    cur_function += line + '\n'

def _file_mismatch(expected, actual):
  expected = list(_split_by_function(expected))
  actual = list(_split_by_function(actual))

  i = 0
  while i < len(expected) and i < len(actual):
    if expected[i] != actual[i]:
      return f'Mismatch:\nExpected:\n{expected[i]}\nActual:\n{actual[i]}'
    i += 1

  if i < len(expected):
    return f'Expected has an unmacthed function:\n{expected[i]}'

  if i < len(actual):
    return f'Actual has an unmacthed function:\n{actual[i]}'

  return None



def _compare(expected, actual, missing_is_ok):
    if expected == actual:
      return None

    if not missing_is_ok:
      for file in expected.keys():
        if not file in actual:
          return f'{file} was not generated!'

    for file in actual.keys():
      if not file in expected:
        return f'{file} has no expected!'

      if expected[file] == actual[file]:
        continue

      return _file_mismatch(expected[file], actual[file])



def main():
    options = parse_options()
    actual = run_compilation(options)
    expected = dict(read_expected_results(options.arches))
    test = _compare(expected, actual, options.missing_is_ok)
    if not test:
      exit(0)
    print('\n\nFailure!!!===========\n')
    print(test)
    exit(1)

if __name__ == '__main__':
    main()
