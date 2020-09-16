//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/radindeg.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::radindeg return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::radindeg(T(0)), T);
}

TTS_CASE_TPL("Check eve::radindeg behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::radindeg(-eve::pi(eve::as<T>())   ), (T(-180)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg(-eve::pio_2(eve::as<T>())), (T( -90)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg(-eve::pio_4(eve::as<T>())), (T( -45)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg( (T(0))         ), (T(   0)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg( eve::pio_4(eve::as<T>())), (T(  45)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg( eve::pio_2(eve::as<T>())), (T(  90)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg( eve::pi(eve::as<T>())   ), (T( 180)), 0.5);
}
