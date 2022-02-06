//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cot", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_cot = [](auto e) -> EVE_VALUE { return 1/std::tan(double(e)); };

  if constexpr(eve::platform::supports_denormals)
  {
    eve::uniform_prng<EVE_VALUE> p(-eve::pio_4(eve::as<EVE_VALUE>()), eve::pio_4(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_cot, eve::quarter_circle(eve::cot));
  }
  else
  {
    eve::uniform_prng<EVE_VALUE> p(eve::smallestposval(eve::as<EVE_VALUE>()), eve::pio_4(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_cot, eve::quarter_circle(eve::cot));
  }
};