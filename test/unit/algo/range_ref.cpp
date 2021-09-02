//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <vector>

TTS_CASE("rng_ref")
{
  std::vector<int> v;
  TTS_TYPE_IS(decltype(eve::algo::take_range_ref(v)),                            eve::algo::range_ref<std::vector<int>>);
  TTS_TYPE_IS(decltype(eve::algo::take_range_ref(eve::algo::take_range_ref(v))), eve::algo::range_ref<std::vector<int>>);
  TTS_TYPE_IS(decltype(eve::algo::take_range_ref(eve::algo::as_range(v.begin(), v.end()))),
              (eve::algo::range_pair<std::vector<int>::iterator, std::vector<int>::iterator>));
}
