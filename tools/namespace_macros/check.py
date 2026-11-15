#! /usr/bin/env python3

__copyright__ = "EVE Project Contributors"
__license__   = "BSL-1.0"

import re
import sys
from pathlib import Path

plain_regex  = re.compile(r'^\s*namespace\s+eve([\s{:]|$)')
nested_regex = re.compile(r'EVE_NAMESPACE::[A-Za-z]|^  namespace\s+[A-Za-z]')
macros       = 'use the EVE_*NAMESPACE macros from eve/config/abi_namespace.hpp'

def violation(line):
  if plain_regex.match(line):   return f'opens namespace eve, {macros}'
  if nested_regex.search(line): return f'opens a namespace inside the ABI namespace, {macros}'

def check_file(root, file):
  name = file.relative_to(root).as_posix()
  text = file.read_text(errors='replace')
  return [ f'{name}:{number}: {v}' for number, line in enumerate(text.splitlines(), 1) if (v := violation(line)) ]

skipped = ('include/eve/deps/', 'include/eve/config/')

def check(root):
  root  = Path(root)
  files = sorted(f for f in (root / 'include' / 'eve').rglob('*.hpp')
                   if f.is_file() and not f.relative_to(root).as_posix().startswith(skipped))
  return [ v for f in files for v in check_file(root, f) ]

if __name__ == '__main__':
  violations = check(sys.argv[1] if len(sys.argv) > 1 else Path(__file__).parents[2])
  for v in violations: print(v)
  sys.exit(1 if violations else 0)
