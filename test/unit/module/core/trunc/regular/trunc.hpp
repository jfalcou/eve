//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/trunc.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::trunc return type")
{
  TTS_EXPR_IS(eve::trunc(Type()), (Type));
}

TTS_CASE("Check eve::trunc behavior")
{
  TTS_EQUAL(eve::trunc(Type(0)), (Type(0)));
  TTS_EQUAL(eve::trunc(Type(1)), (Type(1)));
  TTS_EQUAL(eve::trunc(Type(2)), (Type(2)));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::trunc(static_cast<Type>(-1)), (Type(-1)));
    TTS_EQUAL(eve::trunc(static_cast<Type>(-2)), (Type(-2)));
  }

  if constexpr(std::is_floating_point_v<Value>)
  {
   TTS_EQUAL(eve::trunc(static_cast<Type>(-1.3)), (Type(-1)));
   TTS_EQUAL(eve::trunc(static_cast<Type>(-1.5)), (Type(-1)));
   TTS_EQUAL(eve::trunc(static_cast<Type>(-1.6)), (Type(-1)));
   TTS_EQUAL(eve::trunc(static_cast<Type>( 1.3)), (Type( 1)));
   TTS_EQUAL(eve::trunc(static_cast<Type>( 1.5)), (Type( 1)));
   TTS_EQUAL(eve::trunc(static_cast<Type>( 1.6)), (Type( 1)));
  }
}
