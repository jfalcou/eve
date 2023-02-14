//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/wide.hpp>

TTS_CASE("Check for nofs cardinal")
{
#ifndef EVE_AVX512_DEFAULT_64_BYTES
  TTS_EQUAL((eve::nofs_cardinal_v<double, eve::x86_512_>),
            (eve::expected_cardinal_v<double, eve::x86_256_>));
#endif
  TTS_EQUAL((eve::nofs_cardinal_v<double, eve::x86_256_>),
            (eve::expected_cardinal_v<double, eve::x86_256_>));
  TTS_EQUAL((eve::nofs_cardinal_v<double, eve::arm_128_>),
            (eve::expected_cardinal_v<double, eve::arm_128_>));
};

TTS_CASE("Check for nofs_wide")
{
  eve::nofs_wide<int> a{0}, b{1};
  eve::nofs_logical<int> test = a != b;
  TTS_EXPECT(eve::all(test));
};
