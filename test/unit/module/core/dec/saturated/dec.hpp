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
#include <eve/function/saturated.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated_(eve::dec) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::dec)(Type()), (Type));
}

TTS_CASE("Check eve::saturated_(eve::dec) behavior")
{
  using eve::saturated_;

  TTS_EQUAL(saturated_(eve::dec)(eve::Valmin<Type>()), eve::Valmin<Type>());
  TTS_EQUAL(saturated_(eve::dec)(Type(1)), (Type( 0)) );
  TTS_EQUAL(saturated_(eve::dec)(Type(2)), (Type( 1)) );

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(saturated_(eve::dec)(Type(0)), (Type(-1)) );
  }
  else
  {
    TTS_EQUAL(saturated_(eve::dec)(Type(0)), (Type(0)) );
  }
}
