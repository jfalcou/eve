//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sec.hpp>
#include <eve/constant/pio_2.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sec")
{
  auto std_sec = [](auto e) -> EVE_VALUE  { return eve::rec(std::cos(double(e))); };

  eve::uniform_prng<EVE_VALUE> p(-eve::pio_2(eve::as<EVE_VALUE>()), eve::pio_2(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_sec, eve::small(eve::sec));
}
