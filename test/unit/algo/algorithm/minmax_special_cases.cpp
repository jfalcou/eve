//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/algo/algo_test.hpp"

#include <eve/algo.hpp>

TTS_CASE("eve.algo.min/max empty range")
{
  std::vector<int> v{};

  TTS_EQUAL(eve::algo::min_value(v), std::nullopt);
  TTS_EQUAL(eve::algo::min_element(v), v.end());
  TTS_EQUAL(eve::algo::max_value(v), std::nullopt);
  TTS_EQUAL(eve::algo::max_element(v), v.end());
};

TTS_CASE("eve.algo.min/max stability")
{
  std::vector<int> key{ 1, 2, 3, 4, 1 };
  std::vector<int> val{ 4, 1, 2, 3, 0 };

  auto kv = eve::views::zip(key, val);

  auto less_by_key = [](auto x, auto y) {
    return get<0>(x) < get<0>(y);
  };

  auto greater_by_key = [](auto x, auto y) {
    return get<0>(x) > get<0>(y);
  };

  TTS_EQUAL(*eve::algo::min_value(kv, less_by_key), eve::read(kv.begin()));
  TTS_EQUAL(eve::algo::min_element(kv, less_by_key), kv.begin());

  TTS_EQUAL(*eve::algo::max_value(kv, greater_by_key), eve::read(kv.end() - 1));
  TTS_EQUAL(eve::algo::max_element(kv, greater_by_key), kv.end() - 1);
};
