//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/frac.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::frac return type")
{
  TTS_EXPR_IS(eve::frac(Type()), (Type));
}

TTS_CASE("Check eve::frac behavior")
{
  TTS_EQUAL(eve::frac(Type(0)), Type(0));
  TTS_EQUAL(eve::frac(Type(2)), Type(0));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::frac(static_cast<Type>(-2)), (Type(0)) );
    TTS_EQUAL(eve::frac(static_cast<Type>(1)) , (Type(0)) );
  }

  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::frac(Type(-3/2.)), Type(-0.5));
    TTS_EQUAL(eve::frac(Type( 3/2.)), Type( 0.5));

    TTS_ULP_EQUAL(eve::frac(Type( 4/3.)), (Type( 1/3.)), 0.5);
    TTS_ULP_EQUAL(eve::frac(Type(-4/3.)), (Type(-1/3.)), 0.5);
  }
}
