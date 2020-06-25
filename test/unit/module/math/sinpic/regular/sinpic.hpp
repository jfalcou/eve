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
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE_TPL("Check eve::sinpic return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinpic(T(0)), T);
}

TTS_CASE_TPL("Check eve::sinpic behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::sinpic(T(0)), T(1), 0.5);
  TTS_ULP_EQUAL(eve::sinpic(-T(1)/T(2)), T(2)/(eve::Pi<T>()), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(-T(1)/T(4)), eve::sinpi(T(1)/T(4))*T(4)/(eve::Pi<T>()), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(T(1)/T(2)),  T(2)/(eve::Pi<T>()), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(T(1)/T(4)), eve::sinpi(T(1)/T(4))*T(4)/(eve::Pi<T>()), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(eve::Eps<T>()), eve::One<T>(), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(eve::Zero<T>()), eve::One<T>(), 1.0);

}
