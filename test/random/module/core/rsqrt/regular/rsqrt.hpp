//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rsqrt.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on rsqrt")
{
  auto std_rsqrt = [](auto e) { return EVE_VALUE(1)/std::sqrt(e); };

  eve::uniform_prng<EVE_VALUE> p(eve::smallestposval(eve::as<EVE_VALUE>()), EVE_VALUE(eve::valmax(eve::as<float>())));
  TTS_RANGE_CHECK(p, std_rsqrt, eve::rsqrt);
}
