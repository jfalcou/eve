import os

import constants

def _filter_files(files, arches):
  if not arches:
    return files

  suffixes = [arch + '.s' for arch in arches]
  actual_files = []
  for f in files:
    for s in suffixes:
      if f.endswith(s):
        actual_files.append(f)
  return actual_files

def read_expected_results(arches=None):
  files = os.listdir(constants.EXPECTED_DIR)
  files = _filter_files(files, arches)
  for file in files:
      with open(constants.EXPECTED_DIR.joinpath(file), 'r') as f:
        yield file, f.read()
