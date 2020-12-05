import pathlib

ALL_ARCHES = [
  'sse2',
  'sse3',
  'ssse3',
  'sse4',
  'avx',
  'avx2'
]

CURRENT_DIR = pathlib.Path(__file__).parent.absolute()

#              scripts     asm    test   eve
EVE_INCLUDE  = CURRENT_DIR.parent.parent.parent.joinpath('include')
TEST_SOURCES = CURRENT_DIR.parent.joinpath('sources')
EXPECTED_DIR = CURRENT_DIR.parent.joinpath('expected')
