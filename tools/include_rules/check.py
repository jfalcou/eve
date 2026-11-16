#! /usr/bin/env python3

__copyright__ = "EVE Project Contributors"
__license__   = "BSL-1.0"

import re
import sys
from pathlib import Path

include_regex = re.compile(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]')

sources = [ ('include', '*.hpp'),
            ('test', '*.hpp'), ('test', '*.cpp'),
            ('benchmarks', '*.hpp'), ('benchmarks', '*.cpp'),
            ('examples', '*.hpp'), ('examples', '*.cpp') ]

def include_path(root, file):
  try:               return file.relative_to(root / 'include').as_posix()
  except ValueError: return None

# The tests of a folder, under test/unit/, may include its private headers
def tested_path(name):
  return 'eve/' + name.removeprefix('test/unit/') if name.startswith('test/unit/') else None

def in_folder(path, folder, rules):
  return path is not None and (path.startswith(folder + '/') or path == rules.PRIVATE_FOLDERS.get(folder))

def allowed(include, patterns):
  return any(include.startswith(p) if p.endswith('/') else include == p for p in patterns)

def check_file(root, file, rules):
  path       = include_path(root, file)
  name       = file.relative_to(root).as_posix()
  text       = file.read_text(errors='replace')
  tested     = tested_path(name)
  violations = []

  for number, line in enumerate(text.splitlines(), 1):
    match = include_regex.match(line)
    if not match: continue
    include = match.group(1)
    for folder, entry in rules.PRIVATE_FOLDERS.items():
      if include.startswith(folder + '/') and not in_folder(path, folder, rules) \
                                          and not in_folder(tested, folder, rules):
        violations.append(f'{name}:{number}: includes {include}, only {entry} may be included outside of {folder}')

    for folder, patterns in rules.LAYERS.items():
      if include.startswith('eve/') and in_folder(path, folder, rules) and not in_folder(include, folder, rules) \
                                    and not allowed(include, patterns):
        violations.append(f'{name}:{number}: includes {include}, {folder} may only include itself and {", ".join(patterns)}')

  return violations

def check(root, rules):
  root  = Path(root)
  files = sorted({ f for folder, pattern in sources for f in (root / folder).rglob(pattern) if f.is_file() })
  return [ v for f in files for v in check_file(root, f, rules) ]

if __name__ == '__main__':
  sys.path.insert(0, str(Path(__file__).parent))
  import rules
  violations = check(sys.argv[1] if len(sys.argv) > 1 else Path(__file__).parents[2], rules)
  for v in violations: print(v)
  sys.exit(1 if violations else 0)
