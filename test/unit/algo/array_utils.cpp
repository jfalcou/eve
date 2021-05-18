//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/algo/array_utils.hpp>

#include <algorithm>
#include <functional>

TTS_CASE("eve.algo.array_utils array_map")
{
  constexpr std::array<char, 4>   input = { 1, 2, 3, 4  };
  constexpr std::array<int, 4> expected = { 2, 4, 6, 8 };
  constexpr auto actual = eve::algo::array_map(input, [](char x) -> int { return x * 2; });
  TTS_CONSTEXPR_EXPECT(expected == actual);
}

TTS_CASE("eve.algo.array_utils array_map")
{
  {
    constexpr std::array in = {1, 2, 3, 4, 5};
    constexpr int actual = eve::algo::array_reduce(in, std::plus<>{});
    constexpr int expected = 1 + 2 + 3 + 4 + 5;
    TTS_CONSTEXPR_EXPECT( expected == actual );
  }
  {
    constexpr std::array in = {15, 0, -5, 13};
    constexpr int actual = eve::algo::array_reduce(in, [](auto x, auto y) { return std::min(x, y); });
    TTS_CONSTEXPR_EXPECT( actual == -5 );
  }
  {
    constexpr std::array in = {1};
    constexpr int actual = eve::algo::array_reduce(in, std::plus<>{});
    TTS_CONSTEXPR_EXPECT( actual == 1 );
  }
}
