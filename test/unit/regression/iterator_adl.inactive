//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>

TTS_CASE("soa_vector should not be hindered by ADL-found operators from its value type")
{
  eve::complex<float> z{1.35,6.87};
  eve::algo::soa_vector<eve::complex<float>> x = {z,z,z,z};
  TTS_PASS("Correct by design");
};
