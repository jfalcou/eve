//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/constant/pio_4.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on tan", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_tan = [](auto e) { return std::tan(e); };

  eve::uniform_prng<EVE_VALUE> p(-eve::pio_4(eve::as<EVE_VALUE>()), eve::pio_4(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_tan, eve::quarter_circle(eve::tan));
};