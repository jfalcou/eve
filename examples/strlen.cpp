//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"

#include <eve/eve.hpp>
#include <eve/function/first_true.hpp>
#include <eve/function/load.hpp>
#include <eve/memory/aligned_allocator.hpp>

std::size_t strlen_example(const char* s_) {
  const auto* s = reinterpret_cast<const std::uint8_t*>(s_);
  using wide = eve::wide<std::uint8_t>;

  const wide zeroes{0};

  eve::aligned_ptr aligned_s = eve::previous_aligned_address(s);

  wide cur = eve::unsafe(eve::load)(aligned_s);
  eve::ignore_first ignore{s - aligned_s.get()};

  std::optional match = eve::first_true[ignore](cur == zeroes);

  while (!match) {
    aligned_s += wide::size();
    cur = eve::unsafe(eve::load)(aligned_s);
    match = eve::first_true(cur == zeroes);
  }

  return static_cast<std::size_t>(aligned_s.get() + *match - s);
}

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
