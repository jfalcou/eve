//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpic.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE("Check eve::sinpic return type")
{
  TTS_EXPR_IS(eve::sinpic(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::sinpic behavior")
{
  TTS_ULP_EQUAL(eve::sinpic(EVE_TYPE(0)), EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL(eve::sinpic(-EVE_TYPE(1)/EVE_TYPE(2)), EVE_TYPE(2)/(eve::pi(eve::as<EVE_TYPE>())), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(-EVE_TYPE(1)/EVE_TYPE(4)), eve::sinpi(EVE_TYPE(1)/EVE_TYPE(4))*EVE_TYPE(4)/(eve::pi(eve::as<EVE_TYPE>())), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(EVE_TYPE(1)/EVE_TYPE(2)),  EVE_TYPE(2)/(eve::pi(eve::as<EVE_TYPE>())), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(EVE_TYPE(1)/EVE_TYPE(4)), eve::sinpi(EVE_TYPE(1)/EVE_TYPE(4))*EVE_TYPE(4)/(eve::pi(eve::as<EVE_TYPE>())), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(eve::eps(eve::as<EVE_TYPE>())), eve::one(eve::as<EVE_TYPE>()), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(eve::zero(eve::as<EVE_TYPE>())), eve::one(eve::as<EVE_TYPE>()), 1.0);

}
