//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/pi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cos", EVE_TYPE)
{
  auto std_cos = [](auto e) -> EVE_VALUE { return std::cos(double(e)); };

  eve::uniform_prng<EVE_VALUE> p(-eve::pi(eve::as<EVE_VALUE>()), eve::pi(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_cos, eve::circle(eve::cos));
}
