//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/indeg.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::indeg return type")
{
  TTS_EXPR_IS(eve::indeg(Type(0)), (Type));
}

TTS_CASE("Check eve::indeg behavior")
{
  TTS_ULP_EQUAL(eve::indeg(-eve::Pi<Type>()   ), (Type(-180)), 0.5);
  TTS_ULP_EQUAL(eve::indeg(-eve::Pio_2<Type>()), (Type( -90)), 0.5);
  TTS_ULP_EQUAL(eve::indeg(-eve::Pio_4<Type>()), (Type( -45)), 0.5);
  TTS_ULP_EQUAL(eve::indeg( (Type(0))         ), (Type(   0)), 0.5);
  TTS_ULP_EQUAL(eve::indeg( eve::Pio_4<Type>()), (Type(  45)), 0.5);
  TTS_ULP_EQUAL(eve::indeg( eve::Pio_2<Type>()), (Type(  90)), 0.5);
  TTS_ULP_EQUAL(eve::indeg( eve::Pi<Type>()   ), (Type( 180)), 0.5);
}
