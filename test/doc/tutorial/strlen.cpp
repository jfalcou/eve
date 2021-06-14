//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include "strlen.hpp"

#include <eve/memory/aligned_allocator.hpp>

TTS_CASE( "Check strlen example" )
{
 std::vector<char, eve::aligned_allocator<char, eve::fixed<4096>>> page(4096, 'a');

  // 50 from the beginning
  auto* f = page.data();
  auto* l = f + 50;

  auto run = [&] {
    *l = 0;
    for (auto* it = f; it < l; ++it) {
      std::size_t expected = static_cast<std::size_t>(l - it);
      TTS_EQUAL(expected, strlen_example(it));
    }
    *l = 'a';
  };

  while (f < l) {
    run();
    --l;
    *f = 1;
    ++f;
  }

  // 50 from the end
  f = page.data() + page.size() - 50;
  l = page.data() + page.size() - 1;

  while (f < l) {
    run();
    --l;
    ++f;
  }
}
