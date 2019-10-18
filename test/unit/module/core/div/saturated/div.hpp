//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check saturated_(eve::div) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::div)(Type(), Type()), (Type));
}

TTS_CASE("Check saturated_(eve::div) behavior")
{
  using eve::saturated_;

  if constexpr(std::is_integral_v<Value>)
  {
    auto vmax = eve::Valmax<Type>();
    auto vmin = eve::Valmin<Type>();

    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(saturated_(eve::div)(vmax       , (Type(-1))), vmin+(Type(1)));
      TTS_EQUAL(saturated_(eve::div)(vmin       , (Type(-1))), vmax);
      TTS_EQUAL(saturated_(eve::div)((Type(-1)) , (Type( 0))), vmin);
      TTS_EQUAL(saturated_(eve::div)((Type(-2)) , (Type( 0))), vmin);
      TTS_EQUAL(saturated_(eve::div)(vmin       , (Type( 0))), vmin);
      TTS_EQUAL(saturated_(eve::div)((Type(1))  , (Type( 0))), vmax);
      TTS_EQUAL(saturated_(eve::div)((Type(2))  , (Type( 0))), vmax);
      TTS_EQUAL(saturated_(eve::div)(vmax       , (Type( 0))), vmax);
    }
    else
    {
      TTS_EQUAL(saturated_(eve::div)(vmax     , (Type(1))), vmax);
      TTS_EQUAL(saturated_(eve::div)((Type(1)), (Type(0))), vmax);
      TTS_EQUAL(saturated_(eve::div)((Type(2)), (Type(0))), vmax);
      TTS_EQUAL(saturated_(eve::div)(vmax     , (Type(0))), vmax);
    }
  }
  else
  {
    TTS_EQUAL(saturated_(eve::div)(Type( 0) , Type(1)), Type(0  ) );
    TTS_EQUAL(saturated_(eve::div)(Type( 1) , Type(1)), Type(1  ) );
    TTS_EQUAL(saturated_(eve::div)(Type(12) , Type(4)), Type(3  ) );
    TTS_EQUAL(saturated_(eve::div)(Type( 1) , Type(2)), Type(0.5) );
  }
}
