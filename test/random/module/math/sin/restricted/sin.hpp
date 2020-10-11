//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/constant/pio_4.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sin", EVE_TYPE)
{
  auto std_sin = [](auto e) { return std::sin(e); };

  eve::uniform_prng<EVE_VALUE> p(-eve::pio_4(eve::as<EVE_VALUE>()), eve::pio_4(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_sin, eve::restricted(eve::sin));
}
