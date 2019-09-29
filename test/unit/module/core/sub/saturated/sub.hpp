//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SUB_HPP
#define SUB_HPP

#include <eve/function/scalar/sub.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>
 
TTS_CASE("Check sub return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::sub)(Type(), Type()), Type);
}

TTS_CASE("Check eve::saturated_(eve::sub) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::sub)(Type{0}, Type{0}), Type(0));
  TTS_EQUAL(eve::saturated_(eve::sub)(Type{1}, Type{1}), Type(0));
  TTS_EQUAL(eve::saturated_(eve::sub)(Type{2}, Type{2}), Type(0));
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::sub)(eve::Valmin<Type>(),eve::One<Type>()), eve::Valmin<Type>());
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::saturated_(eve::sub)(eve::Valmax<Type>(),eve::Mone<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::sub)(Type(-1), Type(1)), Type(-2));
      TTS_EQUAL(eve::saturated_(eve::sub)(Type(-2), Type(-6)), Type(4));
    }
  }
}

#endif
