#! /usr/bin/env python3

__copyright__ = "EVE Project Contributors"
__license__   = "BSL-1.0"

import subprocess
import re
from collections import Counter
from pathlib import Path
import multiprocessing as mp

project_root = Path(subprocess.check_output(["git", "rev-parse", "--show-toplevel"]).strip().decode('utf-8'))

abis = { 'arm_abi': 'arm/neon', 'sve_abi': 'arm/sve', 'x86abi': 'x86', 'ppc_abi': 'ppc' }
callable_def_regex = re.compile(r'\bstruct\s+(\w+?)_t\s*?:\s*?(callable|strict_elementwise_callable|elementwise_callable|strict_tuple_callable|tuple_callable|constant_callable)')
include_regex = re.compile(r'^\s*?#\s*?include\s*?<(.*?)>', re.MULTILINE)

file_cache = { }

def populate_file_cache():
  for file in project_root.glob('include/eve/**/*.hpp'):
    content = file.read_text()
    includes = Counter(include_regex.findall(content))
    file_cache[str(file)] = (content, includes)

# checks that no file contains multiple different arch tags
def check_arch_tags():
  specs = { 'sse2_': 'x86', 'ssse3_': 'x86', 'sse4.1_': 'x86',
          'sse4.2_': 'x86', 'avx_': 'x86',  'avx2_': 'x86',
          'avx512_': 'x86', 'neon128': 'arm/neon', 'sve_': 'arm/sve', 'vmx_':'ppc' }

  archs = [ 'arm/neon', 'arm/sve', 'ppc', 'riscv', 'x86' ]

  for fname, (content, _) in file_cache.items():
    for arch in archs:
      if arch in fname:
        for spec, s_arch in specs.items():
          if spec in content and s_arch is not arch:
            print(f"{fname}: Found {spec} ({s_arch}) tag when the detected arch was {arch}")

        for abi, a_arch in abis.items():
          if abi in content and a_arch is not arch:
            print(f"{fname}: Found {abi} ({a_arch}) tag when the detected arch was {arch}")

        break
    else:
      continue

# checks that no file contains multiple different callables implementations
callable_behavior_call = re.compile(r'(\w+?)\.(?:behavior|retarget)\(')

def check_callables_defs__check_file(file, content, regex):
  callable_multidef_ignorelist = [ "extract", "insert", "lentz_a", "lentz_b" ]
  callable_chainuse_ignorelist = [ ("rshl", "shl"), ("rshl", "shr"), ("rshr", "shl"), ("rshr", "shr"), ("shr", "shl") ]
  found = set(regex.findall(content))
  if len(found) > 1 and not all(cname in callable_multidef_ignorelist for cname in found):
    print(f"Multiple callable impl defined in {file}:\n\t{found}")

  if len(found) > 0:
    callable_name = found.pop()
    for match in callable_behavior_call.findall(content):
      if match != callable_name and (callable_name, match) not in callable_chainuse_ignorelist:
        print(f"Callable {callable_name} defined in {file} but {match} is used")


def check_callables_defs():
  files_searched = { }
  callables = { }

  # get all callables
  for file, (content, _) in file_cache.items():
    files_searched[file] = content

    for cname, ctype in callable_def_regex.findall(content):
      if cname in callables:
        print(f"Callable {cname} already defined in {callables[cname]['file']}")
      else:
        callables[cname] = { 'file': file, 'type': ctype }

  combined_regex = re.compile(r'(' + '|'.join(cname for cname in callables) + r')_\s*?\(\s*?EVE_REQUIRES')

  with mp.Pool() as pool:
    pool.starmap(
      check_callables_defs__check_file,
      [(file, content, combined_regex) for file, content in files_searched.items()]
    )

# check for duplicate include directives
def check_dup_includes():
  for file, (_, includes) in file_cache.items():
    duplicates = [inc for inc, count in includes.items() if count > 1]
    if len(duplicates) > 0:
      print(f"Multiple includes of {duplicates} in {file}")

# check for orphan header files
def check_orphan_headers():
  orphan_ignorelist = [
    "eve/std.hpp",
    "eve/memory.hpp",
    "eve/arch/detection.hpp",
    
    "eve/module/algo.hpp",
    "eve/module/bessel.hpp",
    "eve/module/combinatorial.hpp",
    "eve/module/elliptic.hpp",
    "eve/module/polynomial.hpp",
  ]

  referenced = set()
  for _, (_, includes) in file_cache.items():
    referenced.update(includes.keys())

  for file, _ in file_cache.items():
    cut_path = file.split('include/')[1]
    if cut_path not in referenced and cut_path not in orphan_ignorelist:
      print(f"Found orphan header: {cut_path}")

if __name__ == '__main__':
  populate_file_cache()
  
  check_arch_tags()
  check_callables_defs()
  check_dup_includes()
  check_orphan_headers()

  print("done")
