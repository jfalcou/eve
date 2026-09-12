#!/usr/bin/env python3
# Copacabana - Common CMake Package Tools
# Copyright : Copacabana Project Contributors
# SPDX-License-Identifier: BSL-1.0
import argparse
import re
import sys


def process_text(text, prefix):
  """
  Identifies types starting with _:: (and any leading namespaces)
  and replaces them with '{prefix}_implementation_defined', correctly
  handling C++ template bracket balancing (< >).

  Test Cases:
  # Basic replacement
    >>> process_text("_::simple_type", prefix="lib")
    'lib_implementation_defined'

    >>> # Replacement with explicit namespace
    >>> process_text("lib::_::simple_type", prefix="lib")
    'lib_implementation_defined'

    >>> # Handling const and namespaces
    >>> process_text("const lib::_::simple_type", prefix="lib")
    'const lib_implementation_defined'

    >>> # Handling nested namespaces
    >>> process_text("outer::inner::_::type", prefix="lib")
    'lib_implementation_defined'

    >>> # Handling prefix operators
    >>> process_text("!_::value_of<X>", prefix="lib")
    '!lib_implementation_defined'

    >>> # Handling complex templates
    >>> process_text("_::some_code<T, U, 4 >", prefix="std")
    'std_implementation_defined'
  """
  # The regex now captures any number of 'namespace::' sequences before _::
  # ([a-zA-Z0-9_]+::)* matches 'lib::', 'a:🅱️:', or nothing.
  pattern = re.compile(r'([a-zA-Z0-9_]+::)*_::[a-zA-Z0-9_]+')
  replacement_token = f"{prefix}_implementation_defined"
  offset = 0
  result = []

  while True:
    match = pattern.search(text, offset)
    if not match:
      result.append(text[offset:])
      break

    result.append(text[offset:match.start()])

    remaining = text[match.end():]
    if remaining.startswith('<'):
      count = 0
      idx = 0
      for char in remaining:
        if char == '<':
          count += 1
        elif char == '>':
          count -= 1
        idx += 1
        if count == 0:
          break

      result.append(replacement_token)
      offset = match.end() + idx
    else:
      result.append(replacement_token)
      offset = match.end()

  return "".join(result)

def main():
  parser = argparse.ArgumentParser(description="Filter C++ implementation details for Doxygen.")
  parser.add_argument("file", nargs="?", help="Input file to process")
  parser.add_argument("--test", action="store_true", help="Run doctests")
  parser.add_argument("-p", "--prefix", required=True, help="Prefix for the replacement string")

  args = parser.parse_args()

  if args.test:
    import doctest
    result = doctest.testmod(optionflags=doctest.NORMALIZE_WHITESPACE)
    if result.failed == 0:
      print(f"Success: All {result.attempted} tests passed.")
    sys.exit(0)

  if not args.file:
    parser.print_help()
    sys.exit(1)

  try:
    with open(args.file, 'r') as f:
      content = f.read()

    print(process_text(content, prefix=args.prefix), end='')
  except FileNotFoundError:
    sys.stderr.write(f"Error: File {args.file} not found.\n")
    sys.exit(1)

if __name__ == "__main__":
  main()
