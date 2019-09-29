//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DEC_HPP
#define DEC_HPP

#include <eve/function/scalar/dec.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>  
#include <type_traits>
 
TTS_CASE("Check dec return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::dec)(Type()), Type);
  TTS_EXPR_IS(eve::saturated_(eve::dec[eve::logical<Type>()])(Type()), Type);
}

TTS_CASE("Check saturated_(dec) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::dec)(eve::Valmin<Type>()), eve::Valmin<Type>());
  TTS_EQUAL(eve::saturated_(eve::dec)(Type{1}), Type(0));
  TTS_EQUAL(eve::saturated_(eve::dec)(Type{2}), Type(1));
  TTS_EQUAL(eve::saturated_(eve::dec[ Type(1) > Type(0) ])(Type(1)), Type(0));
  TTS_EQUAL(eve::saturated_(eve::dec[ Type(1) > Type(2) ])(eve::Zero<Type>()), Type(0));

  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::dec)(static_cast<Type>(-2)), Type(-3));
    TTS_EQUAL(eve::saturated_(eve::dec[ Type(-1) > Type(0) ])(eve::Zero<Type>()), Type(0));
  }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::dec)(eve::Mzero<Type>()), Type(-1));
    TTS_EQUAL(eve::saturated_(eve::dec)(eve::Zero<Type>()), Type(-1));
  }
}

#endif
