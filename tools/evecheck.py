#! /usr/bin/env python3

import subprocess
import re
from collections import Counter
from pathlib import Path
import multiprocessing as mp

project_root = Path(subprocess.check_output(["git", "rev-parse", "--show-toplevel"]).strip().decode('utf-8'))

abis = { 'arm_abi': 'arm/neon', 'sve_abi': 'arm/sve', 'x86abi': 'x86', 'ppc_abi': 'ppc' }
callable_def_regex = re.compile(r'\bstruct\s+(\w+_)t\s*:\s*(callable|strict_elementwise_callable|elementwise_callable|strict_tuple_callable|tuple_callable|constant_callable)')

# checks that no file contains multiple different arch tags
def check_arch_tags():
  specs = { 'sse2_': 'x86', 'ssse3_': 'x86', 'sse4.1_': 'x86',
          'sse4.2_': 'x86', 'avx_': 'x86',  'avx2_': 'x86',
          'avx512_': 'x86', 'neon128': 'arm/neon', 'sve_': 'arm/sve', 'vmx_':'ppc' }

  archs = [ 'arm/neon', 'arm/sve', 'ppc', 'riscv', 'x86' ]

  for file in project_root.glob('include/eve/module/**/*.hpp'):
    fname = str(file)

    for arch in archs:
      if arch in fname:
        content = file.read_text()

        for spec, s_arch in specs.items():
          if spec in content and s_arch is not arch:
            print(f"{fname}: Found {spec} ({s_arch}) tag when the detected arch was {arch}")

        for abi, a_arch in abis.items():
          if abi in content and a_arch is not arch:
            print(f"{fname}: Found {abi} ({a_arch}) tag when the detected arch was {arch}")

        break
    else:
      continue

def check_callables_defs__check_file(file, content, regex):
  found = set(regex.findall(content))
  if len(found) > 1:
    print(f"Multiple callables defined in {file}:\n\t{found}")

# checks that no file contains multiple different callables implementations
def check_callables_defs():
  files_searched = { }
  callables = { }

  # get all callables
  for file in project_root.glob('include/eve/module/**/*.hpp'):
    content = file.read_text()
    files_searched[file] = content
    matchs = callable_def_regex.findall(content)

    for cname, ctype in matchs:
      if cname in callables:
        print(f"Callable {cname} already defined in {callables[cname]['file']}")
      else:
        callables[cname] = { 'file': file, 'type': ctype }

  print(f"found {len(callables)} callables")
  combined_regex = re.compile(r'\s+(' + '|'.join(cname for cname in callables) + r')\s*\(\s*EVE_REQUIRES')

  with mp.Pool() as pool:
    pool.starmap(
      check_callables_defs__check_file,
      [(file, content, combined_regex) for file, content in files_searched.items()]
    )

def check_dup_includes():
  include_regex = re.compile(r'^#include\s*<(.*?)>', re.MULTILINE)
  for file in project_root.glob('include/eve/**/*.hpp'):
    content = file.read_text()
    includes = Counter(include_regex.findall(content))

    duplicates = [inc for inc, count in includes.items() if count > 1]
    if len(duplicates) > 0:
      print(f"Multiple includes of {duplicates} in {file}")

check_arch_tags()
check_callables_defs()
check_dup_includes()

print("done")
