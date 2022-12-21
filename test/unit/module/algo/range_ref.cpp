//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <vector>

TTS_CASE("rng_ref")
{
  std::vector<int> v;
  TTS_TYPE_IS(decltype(eve::algo::range_ref(v)),                       eve::algo::range_ref_wrapper<std::vector<int>>);
  TTS_TYPE_IS(decltype(eve::algo::range_ref(eve::algo::range_ref(v))), eve::algo::range_ref_wrapper<std::vector<int>>);
  TTS_TYPE_IS(decltype(eve::algo::range_ref(eve::algo::as_range(v.begin(), v.end()))),
              (eve::algo::as_range<std::vector<int>::iterator, std::vector<int>::iterator>));
};
