//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on tan", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_tan = [](auto e) -> EVE_VALUE { return std::tan(double(e)); };

  eve::uniform_prng<EVE_VALUE> p(-eve::pio_2(eve::as<EVE_VALUE>()), eve::pio_2(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_tan, eve::half_circle(eve::tan));
};