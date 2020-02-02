//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dist.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check saturated_(eve::dist) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::dist)(Type(), Type()), (Type));
}

TTS_CASE("Check saturated_(eve::dist) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::dist)(Type(0), Type(0)), (Type(0)));
  TTS_EQUAL(eve::saturated_(eve::dist)(Type(1), Type(5)), (Type(4)));

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL ( eve::saturated_(eve::dist)(eve::Valmax<Type>(),eve::Valmin<Type>())
              , eve::Valmax<Type>()
              );

    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::saturated_(eve::dist)(eve::Valmin<Type>(),Type(-1)), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::dist)(eve::Valmin<Type>(),Type( 0)), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::dist)(Type(-1), Type(1) ), (Type(2)));
      TTS_EQUAL(eve::saturated_(eve::dist)(Type(-2), Type(-6)), (Type(4)));
    }
  }
}
