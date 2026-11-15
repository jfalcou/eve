#! /usr/bin/env python3

__copyright__ = "EVE Project Contributors"
__license__   = "BSL-1.0"

import tempfile
import unittest
from pathlib import Path

import check

plain  = 'opens namespace eve, use the EVE_*NAMESPACE macros from eve/config/abi_namespace.hpp'
nested = 'opens a nested eve namespace by hand, use the EVE_*NAMESPACE macros from eve/config/abi_namespace.hpp'

class NamespaceMacros(unittest.TestCase):
  def setUp(self):
    self.dir  = tempfile.TemporaryDirectory()
    self.root = Path(self.dir.name)
    self.write('include/eve/config/abi_namespace.hpp',
               '#  define EVE_ALGO_NAMESPACE       namespace eve::algo::inline EVE_ABI_NAMESPACE\n'
               '#  define EVE_ALGO_VIEWS_NAMESPACE namespace eve::algo::views::inline EVE_ABI_NAMESPACE\n'
               '#  define EVE_PLATFORM_NAMESPACE   namespace eve::platform::inline EVE_ABI_NAMESPACE\n')

  def tearDown(self):
    self.dir.cleanup()

  def write(self, name, text):
    file = self.root / name
    file.parent.mkdir(parents=True, exist_ok=True)
    file.write_text(text)

  def violations(self):
    return check.check(self.root)

  def test_macros_are_allowed(self):
    self.write('include/eve/wide.hpp', 'EVE_NAMESPACE\n{\n}\nEVE_ABI_INDEPENDENT_NAMESPACE\n{\n}\nEVE_ALGO_NAMESPACE\n{\n}\n')
    self.assertEqual(self.violations(), [])

  def test_plain_namespace_eve_is_rejected(self):
    self.write('include/eve/a.hpp', 'namespace eve\n{\n}\n')
    self.write('include/eve/b.hpp', '  namespace eve::detail {\n}\nnamespace eve{}\n')
    self.assertEqual(self.violations(),
      [ 'include/eve/a.hpp:1: ' + plain
      , 'include/eve/b.hpp:1: ' + plain
      , 'include/eve/b.hpp:3: ' + plain
      ])

  def test_nested_namespace_is_rejected(self):
    self.write('include/eve/a.hpp', 'EVE_NAMESPACE\n{\n  namespace algo\n  {\n  }\n}\nEVE_NAMESPACE::views {}\n')
    self.write('include/eve/b.hpp', 'EVE_NAMESPACE\n{\n\tnamespace platform {}\n    namespace algo::views {}\n}\n'
                                    'EVE_NAMESPACE { namespace views {} }\nEVE_ALGO_NAMESPACE::views {}\n')
    self.assertEqual(self.violations(),
      [ 'include/eve/a.hpp:3: ' + nested
      , 'include/eve/a.hpp:7: ' + nested
      , 'include/eve/b.hpp:3: ' + nested
      , 'include/eve/b.hpp:4: ' + nested
      , 'include/eve/b.hpp:6: ' + nested
      , 'include/eve/b.hpp:7: ' + nested
      ])

  def test_other_nested_namespaces_and_comments_are_allowed(self):
    self.write('include/eve/a.hpp', 'EVE_NAMESPACE\n{\n  namespace std {}\n  namespace algorithm {}\n  //! @namespace algo\n}\nEVE_NAMESPACE::_::helpers {}\n')
    self.assertEqual(self.violations(), [])

  def test_underscore_namespace_is_allowed(self):
    self.write('include/eve/a.hpp', 'EVE_NAMESPACE\n{\n  namespace _\n  {\n  }\n}\nEVE_NAMESPACE::_ {}\n')
    self.assertEqual(self.violations(), [])

  def test_other_namespaces_are_allowed(self):
    self.write('include/eve/a.hpp', 'namespace evex\n{\n}\nnamespace std {}\n')
    self.assertEqual(self.violations(), [])

  def test_deps_config_and_other_folders_are_skipped(self):
    self.write('include/eve/deps/kumi.hpp'           , 'namespace eve {}\n')
    self.write('include/eve/config/abi_namespace.hpp', 'namespace eve {}\n')
    self.write('test/unit/a.hpp'                     , 'namespace eve {}\n')
    self.assertEqual(self.violations(), [])

if __name__ == '__main__':
  unittest.main()
