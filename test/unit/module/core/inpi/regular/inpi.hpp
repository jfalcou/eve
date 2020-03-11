//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inpi.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::inpi return type")
{
  TTS_EXPR_IS(eve::inpi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::inpi behavior")
{
  TTS_ULP_EQUAL(eve::inpi(-eve::Pi<EVE_TYPE>()   ), (EVE_TYPE(-1    )), 0.5);
  TTS_ULP_EQUAL(eve::inpi(-eve::Pi<EVE_TYPE>()/3 ), (EVE_TYPE(-1./3.)), 0.5);
  TTS_ULP_EQUAL(eve::inpi(-eve::Pio_2<EVE_TYPE>()), (EVE_TYPE(-0.5  )), 0.5);
  TTS_ULP_EQUAL(eve::inpi(-eve::Pio_4<EVE_TYPE>()), (EVE_TYPE(-0.25 )), 0.5);
  TTS_ULP_EQUAL(eve::inpi( (EVE_TYPE(0))         ), (EVE_TYPE( 0    )), 0.5);
  TTS_ULP_EQUAL(eve::inpi( eve::Pio_4<EVE_TYPE>()), (EVE_TYPE( 0.25 )), 0.5);
  TTS_ULP_EQUAL(eve::inpi( eve::Pio_2<EVE_TYPE>()), (EVE_TYPE( 0.5  )), 0.5);
  TTS_ULP_EQUAL(eve::inpi( eve::Pi<EVE_TYPE>()/3 ), (EVE_TYPE( 1./3.)), 0.5);
  TTS_ULP_EQUAL(eve::inpi( eve::Pi<EVE_TYPE>()   ), (EVE_TYPE( 1    )), 0.5);
}
