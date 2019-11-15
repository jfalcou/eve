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
  TTS_EXPR_IS(eve::saturate((Type()), eve::as<std::uint32_t>()), (Type));
  TTS_EXPR_IS(eve::saturate((Type()), eve::uint32_            ), (Type));
}

TTS_CASE("Check eve::saturate behavior")
{
  TTS_EQUAL(eve::saturate((Type(0)), eve::uint32_          ), (Type(0))     );
  TTS_EQUAL(eve::saturate((Type(42.69)), eve::uint32_      ), (Type(42.69)) );

  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::saturate(eve::Valmin<Type>(), eve::uint32_), (Type(0)));
    TTS_EQUAL(eve::saturate(eve::Valmax<Type>(), eve::uint32_), (Type(eve::Valmax<std::uint32_t>())) ); 
  }
  else
  {
    if constexpr(std::is_signed_v<Value>)
    {
      if constexpr(sizeof(Value) <= sizeof(std::int32_t))
      {
        TTS_EQUAL(eve::saturate(eve::Valmax<Type>(), eve::uint32_), eve::Valmax<Type>() );
      }
      else
      {
        TTS_EQUAL(eve::saturate(eve::Valmax<Type>(), eve::uint32_), (Type(eve::Valmax<std::uint32_t>())) );
      }
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::Valmax<Type>(), eve::uint32_), (Type(eve::Valmax<std::uint32_t>())) );
    }
  }
}
