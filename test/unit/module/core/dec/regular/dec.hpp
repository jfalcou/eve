//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dec.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::dec return type")
{
  TTS_EXPR_IS(eve::dec(Type(), Type()), (Type));
}

TTS_CASE("Check eve::dec behavior")
{
  TTS_EQUAL(eve::dec(Type(0)), (Type(-1)) );
  TTS_EQUAL(eve::dec(Type(1)), (Type( 0)) );
  TTS_EQUAL(eve::dec(Type(2)), (Type( 1)) );

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::dec(Type(-2)), (Type(-3)));
  }

  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::dec(eve::Mzero<Type>()), (Type(-1)));
  }
}
