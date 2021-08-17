//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/constant/pio_2.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sin", EVE_TYPE)
{
  auto std_sin = [](auto e) -> EVE_VALUE { return std::sin(double(e)); };

  eve::uniform_prng<EVE_VALUE> p(-eve::pio_2(eve::as<EVE_VALUE>()), eve::pio_2(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_sin, eve::small(eve::sin));
}
