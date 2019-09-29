//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DIST_HPP
#define DIST_HPP

#include <eve/function/scalar/dist.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mone.hpp>
#include <type_traits>
 
TTS_CASE("Check dist return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::dist)(Type(), Type()), Type);
}

TTS_CASE("Check eve::saturated_(eve::dist) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::dist)(Type{0}, Type{0}), Type(0));
  TTS_EQUAL(eve::saturated_(eve::dist)(Type{1}, Type{5}), Type(4));
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::dist)(eve::Valmax<Type>(),eve::Valmin<Type>()), eve::Valmax<Type>());
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::saturated_(eve::dist)(eve::Valmin<Type>(),eve::Mone<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::dist)(eve::Valmin<Type>(),eve::Zero<Type>()), eve::Valmax<Type>()); 
      TTS_EQUAL(eve::saturated_(eve::dist)(Type(-1), Type(1)), Type(2));
      TTS_EQUAL(eve::saturated_(eve::dist)(Type(-2), Type(-6)), Type(4));
    }
  }
}

#endif
