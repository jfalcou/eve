#! /usr/bin/env python3

__copyright__ = "EVE Project Contributors"
__license__   = "BSL-1.0"

import tempfile
import types
import unittest
from pathlib import Path

import check

rules = types.SimpleNamespace(
  PRIVATE_FOLDERS    = { 'eve/config': 'eve/config.hpp' },
  LAYERS             = { 'eve/config': ['eve/deps/spy.hpp'] },
  INCLUDED_ONLY_FROM = { 'eve/deps/spy.hpp': 'eve/config' },
)

class IncludeRules(unittest.TestCase):
  def setUp(self):
    self.dir  = tempfile.TemporaryDirectory()
    self.root = Path(self.dir.name)

  def tearDown(self):
    self.dir.cleanup()

  def write(self, name, text):
    file = self.root / name
    file.parent.mkdir(parents=True, exist_ok=True)
    file.write_text(text)

  def violations(self):
    return check.check(self.root, rules)

  def test_entry_header_can_be_included_anywhere(self):
    self.write('include/eve/wide.hpp', '#include <eve/config.hpp>\n')
    self.write('test/unit/a.cpp'     , '#include <eve/config.hpp>\n')
    self.assertEqual(self.violations(), [])

  def test_private_header_cannot_be_included_outside(self):
    self.write('include/eve/wide.hpp', '#include <eve/config/x86/target.hpp>\n')
    self.write('benchmarks/b.cpp'    , '#include <eve/config/arm/target.hpp>\n')
    self.assertEqual(self.violations(),
      [ 'benchmarks/b.cpp:1: includes eve/config/arm/target.hpp, only eve/config.hpp may be included outside of eve/config'
      , 'include/eve/wide.hpp:1: includes eve/config/x86/target.hpp, only eve/config.hpp may be included outside of eve/config'
      ])

  def test_private_header_can_be_included_inside(self):
    self.write('include/eve/config.hpp'    , '#include <eve/config/x86/target.hpp>\n')
    self.write('include/eve/config/x86/target.hpp', '#include <eve/config/arm/target.hpp>\n')
    self.assertEqual(self.violations(), [])

  def test_include_forms(self):
    self.write('test/a.cpp', '  #  include "eve/config/x86/target.hpp"\n#include<eve/config/arm/target.hpp>\n')
    self.assertEqual(len(self.violations()), 2)

  def test_layer_allows_listed_headers_only(self):
    self.write('include/eve/config.hpp', '#include <eve/deps/spy.hpp>\n#include <eve/arch/tags.hpp>\n#include <cstddef>\n')
    self.assertEqual(self.violations(),
      [ 'include/eve/config.hpp:2: includes eve/arch/tags.hpp, eve/config may only include itself and eve/deps/spy.hpp' ])

  def test_layer_allows_its_own_folder(self):
    self.write('include/eve/config/x86/target.hpp', '#include <eve/config/arm/target.hpp>\n#include <eve/config.hpp>\n')
    self.assertEqual(self.violations(), [])

  def test_layer_does_not_apply_outside(self):
    self.write('include/eve/wide.hpp', '#include <eve/arch/tags.hpp>\n')
    self.assertEqual(self.violations(), [])

  def test_tests_of_a_folder_can_include_its_private_headers(self):
    self.write('test/unit/config/a.hpp', '#include <eve/config/x86/target.hpp>\n#include <eve/module/core.hpp>\n')
    self.write('test/unit/arch/b.cpp'  , '#include <eve/config/x86/target.hpp>\n')
    self.write('test/config/c.cpp'     , '#include <eve/config/x86/target.hpp>\n')
    self.assertEqual(self.violations(),
      [ 'test/config/c.cpp:1: includes eve/config/x86/target.hpp, only eve/config.hpp may be included outside of eve/config'
      , 'test/unit/arch/b.cpp:1: includes eve/config/x86/target.hpp, only eve/config.hpp may be included outside of eve/config'
      ])

  def test_header_included_only_from_its_folder(self):
    self.write('include/eve/config/target.hpp', '#include <eve/deps/spy.hpp>\n')
    self.write('include/eve/wide.hpp'         , '#include <eve/deps/spy.hpp>\n')
    self.write('test/unit/config/a.cpp'       , '#include <eve/deps/spy.hpp>\n')
    self.write('examples/b.cpp'               , '#include <eve/deps/spy.hpp>\n')
    self.assertEqual(self.violations(),
      [ 'examples/b.cpp:1: includes eve/deps/spy.hpp, only eve/config may include it'
      , 'include/eve/wide.hpp:1: includes eve/deps/spy.hpp, only eve/config may include it'
      ])

if __name__ == '__main__':
  unittest.main()
