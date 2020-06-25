//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinc.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE_TPL("Check eve::sinc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinc(T(0)), T);
}

TTS_CASE_TPL("Check eve::sinc behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::sinc(T(0)), T(1), 0.5);
  TTS_ULP_EQUAL(eve::sinc(-eve::Pio_2<T>()), T(2)/(eve::Pi<T>()), 0.5);
  TTS_ULP_EQUAL(eve::sinc(-eve::Pio_4<T>()), eve::sin(eve::Pio_4<T>())/(eve::Pio_4<T>()), 0.5);
  TTS_ULP_EQUAL(eve::sinc(eve::Pio_2<T>()),  T(2)/(eve::Pi<T>()), 0.5);
  TTS_ULP_EQUAL(eve::sinc(eve::Pio_4<T>()), eve::sin(eve::Pio_4<T>())/(eve::Pio_4<T>()), 0.5);
  TTS_ULP_EQUAL(eve::sinc(eve::Eps<T>()), eve::One<T>(), 0.5);
  TTS_ULP_EQUAL(eve::sinc(eve::Zero<T>()), eve::One<T>(), 0.5);
}
