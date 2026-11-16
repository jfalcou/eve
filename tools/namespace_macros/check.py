#! /usr/bin/env python3

__copyright__ = "EVE Project Contributors"
__license__   = "BSL-1.0"

import re
import sys
from pathlib import Path

plain_regex  = re.compile(r'^\s*namespace\s+eve([\s{:]|$)')
macro_regex  = re.compile(r'namespace\s+eve::([\w:]+)::inline\s+EVE_ABI_NAMESPACE')
macros       = 'use the EVE_*NAMESPACE macros from eve/config/abi_namespace.hpp'

def nested_regex(root):
  text  = (root / 'include' / 'eve' / 'config' / 'abi_namespace.hpp').read_text()
  names = '|'.join(sorted({ n for path in macro_regex.findall(text) for n in path.split('::') }))
  return re.compile(rf'\bnamespace\s+({names})\b|EVE_\w*NAMESPACE::({names})\b')

def violation(line, nested):
  if plain_regex.match(line):            return f'opens namespace eve, {macros}'
  if nested.search(line.split('//')[0]): return f'opens a nested eve namespace by hand, {macros}'

def check_file(root, file, nested):
  name = file.relative_to(root).as_posix()
  text = file.read_text(errors='replace')
  return [ f'{name}:{number}: {v}' for number, line in enumerate(text.splitlines(), 1) if (v := violation(line, nested)) ]

skipped = ('include/eve/deps/', 'include/eve/config/')

def check(root):
  root  = Path(root)
  files = sorted(f for f in (root / 'include' / 'eve').rglob('*.hpp')
                   if f.is_file() and not f.relative_to(root).as_posix().startswith(skipped))
  nested = nested_regex(root)
  return [ v for f in files for v in check_file(root, f, nested) ]

if __name__ == '__main__':
  violations = check(sys.argv[1] if len(sys.argv) > 1 else Path(__file__).parents[2])
  for v in violations: print(v)
  sys.exit(1 if violations else 0)
