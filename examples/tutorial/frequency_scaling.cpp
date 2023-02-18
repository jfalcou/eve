//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

//! [frequency_scaling_code]

#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>

#include <span>

#ifndef EVE_AVX512_DEFAULT_64_BYTES
static_assert(eve::current_api != eve::avx512 || eve::nofs_cardinal_v<std::int8_t> == 32);
static_assert(eve::current_api != eve::avx512 || eve::expected_cardinal_v<std::int8_t> == 64);
#endif // EVE_AVX512_DEFAULT_64_BYTES

auto find_small_array(std::span<const int> a)
  -> std::span<const int>::iterator
{
  return eve::algo::find_if(a, [](eve::nofs_wide<int> x) { return x < 0; });
}

auto find_large_array(std::span<const int> a)
  -> std::span<const int>::iterator
{
  return eve::algo::find_if[eve::algo::allow_frequency_scaling](a,
    [](eve::wide<int> x) { return x < 0; });
}

auto find_use_4_ints(std::span<const int> a)
  -> std::span<const int>::iterator
{
  return eve::algo::find_if[eve::algo::force_cardinal<4>](a,
    [](eve::wide<int, eve::fixed<4>> x) { return x < 0; });
}
//! [frequency_scaling_code]

#include "test.hpp"

TTS_CASE("Check simple finds") {
  const std::array intsArr {-1, 2, 3, 4, 5, 6};
  std::span<const int> ints{intsArr};
  TTS_EQUAL(0, find_small_array(ints) - ints.begin());
  TTS_EQUAL(0, find_large_array(ints) - ints.begin());
  TTS_EQUAL(0, find_use_4_ints(ints) - ints.begin());
};
