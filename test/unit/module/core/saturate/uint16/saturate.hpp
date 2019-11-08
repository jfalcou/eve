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
  TTS_EXPR_IS(eve::saturate( eve::as<std::uint16_t>(), (Type()) ), (Type));
  TTS_EXPR_IS(eve::saturate( eve::uint16_            , (Type()) ), (Type));
}

TTS_CASE("Check eve::saturate behavior")
{
  TTS_EQUAL(eve::saturate(eve::uint16_, (Type(0))          ), (Type(0))     );
  TTS_EQUAL(eve::saturate(eve::uint16_, (Type(42.69))      ), (Type(42.69)) );

  if constexpr(std::is_signed_v<Value>)
  {
    if constexpr(sizeof(Value) <= sizeof(std::int16_t))
    {
      TTS_EQUAL(eve::saturate(eve::uint16_, eve::Valmax<Type>()), eve::Valmax<Type>() );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::uint16_, eve::Valmax<Type>()), (Type(eve::Valmax<std::uint16_t>())) );
    }
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::uint16_, eve::Valmax<Type>()), (Type(eve::Valmax<std::uint16_t>())) );
  }
}
