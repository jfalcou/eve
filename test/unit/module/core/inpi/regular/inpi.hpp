//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef INPI_HPP
#define INPI_HPP

#include <eve/function/scalar/inpi.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp> 
#include <eve/constant/zero.hpp>
#include <type_traits>

TTS_CASE("Check inpi return type")
{
  TTS_EXPR_IS(eve::inpi(Type(0)),  Type);
}

TTS_CASE("Check eve::inpi behavior")
{
  TTS_ULP_EQUAL(eve::inpi(-eve::Pi<Type>()), -Type(1), 0.5);
  TTS_ULP_EQUAL(eve::inpi(-eve::Pio_2<Type>()), -Type(0.5), 0.5);
  TTS_ULP_EQUAL(eve::inpi(-eve::Pio_4<Type>()), -Type(0.25), 0.5);
  TTS_ULP_EQUAL(eve::inpi(eve::Pi<Type>()), Type(1), 0.5);
  TTS_ULP_EQUAL(eve::inpi(eve::Pio_2<Type>()), Type(0.5), 0.5);
  TTS_ULP_EQUAL(eve::inpi(eve::Pio_4<Type>()), Type(0.25), 0.5);
  TTS_ULP_EQUAL(eve::inpi(eve::Zero<Type>()), eve::Zero<Type>(), 0.5);
}

#endif
