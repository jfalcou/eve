//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturate.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturate return type")
{
  TTS_EXPR_IS(eve::saturate( (Type()),  eve::as<std::int16_t>()), (Type));
  TTS_EXPR_IS(eve::saturate( (Type()),  eve::int16_            ), (Type));
}

TTS_CASE("Check eve::saturate behavior")
{
  if constexpr(std::is_signed_v<Value>)
  {
    if constexpr(sizeof(Value) < sizeof(std::int16_t))
    {
      TTS_EQUAL(eve::saturate( eve::Valmin<Type>(), eve::int16_), eve::Valmin<Type>() );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::Valmin<Type>(), eve::int16_), (Type(eve::Valmin<std::int16_t>())) );
    }
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::Valmin<Type>(), eve::int16_), (Type(0)) );
  }

  TTS_EQUAL(eve::saturate((Type(0))    , eve::int16_      ), (Type(0))     );
  TTS_EQUAL(eve::saturate((Type(42.69)), eve::int16_      ), (Type(42.69)) );

  if constexpr(sizeof(Value) < sizeof(std::int16_t))
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<Type>(), eve::int16_), eve::Valmax<Type>() );
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<Type>(), eve::int16_), (Type(eve::Valmax<std::int16_t>())) );
  }
}
