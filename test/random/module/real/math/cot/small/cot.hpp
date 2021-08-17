//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/constant/pio_2.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cot", EVE_TYPE)
{
  auto std_cot = [](auto e) -> EVE_VALUE { return eve::rec(std::tan(double(e))); };

  eve::uniform_prng<EVE_VALUE> p(-eve::pio_2(eve::as<EVE_VALUE>()), eve::pio_2(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_cot, eve::small(eve::cot));
}
