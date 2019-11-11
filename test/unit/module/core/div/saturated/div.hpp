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
    auto tvmax = eve::Valmax<Type>();
    auto tvmin = eve::Valmin<Type>();
    auto vmax = eve::Valmax<Value>();
    auto vmin = eve::Valmin<Value>();

    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(saturated_(eve::div)(tvmax       , (Type(-1))), tvmin+(Type(1)));
      TTS_EQUAL(saturated_(eve::div)(tvmin       , (Type(-1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Type(-1))  , (Type( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((Type(-2) ) , (Type( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)(tvmin       , (Type( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((Type(1))   , (Type( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Type(2))   , (Type( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(tvmax       , (Type( 0))), tvmax);

      TTS_EQUAL(saturated_(eve::div)(tvmax       , (Value(-1))), tvmin+(Type(1)));
      TTS_EQUAL(saturated_(eve::div)(tvmin       , (Value(-1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Type(-1))  , (Value( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((Type(-2))  , (Value( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)(tvmin       , (Value( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((Type(1))   , (Value( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Type(2))   , (Value( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(tvmax       , (Value( 0))), tvmax);

      TTS_EQUAL(saturated_(eve::div)(vmax        , (Type(-1))), tvmin+(Type(1)));
      TTS_EQUAL(saturated_(eve::div)(vmin        , (Type(-1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Value(-1)) , (Type( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((Value(-2)) , (Type( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)(vmin        , (Type( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((Value(1))  , (Type( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Value(2))  , (Type( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(vmax        , (Type( 0))), tvmax);
     }
    else
    {
      TTS_EQUAL(saturated_(eve::div)(tvmax    , (Type(1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Type(1)), (Type(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Type(2)), (Type(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(tvmax    , (Type(0))), tvmax);

      TTS_EQUAL(saturated_(eve::div)(vmax      , (Type(1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Value(1)), (Type(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Value(2)), (Type(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(vmax      , (Type(0))), tvmax);

     TTS_EQUAL(saturated_(eve::div)(tvmax     , (Value(1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Type(1)) , (Value(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((Type(2)) , (Value(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(tvmax     , (Value(0))), tvmax);
    }
  }
  else
  {
    TTS_EQUAL(saturated_(eve::div)(Type( 0) , Type(1)), Type(0  ) );
    TTS_EQUAL(saturated_(eve::div)(Type( 1) , Type(1)), Type(1  ) );
    TTS_EQUAL(saturated_(eve::div)(Type(12) , Type(4)), Type(3  ) );
    TTS_EQUAL(saturated_(eve::div)(Type( 1) , Type(2)), Type(0.5) );

    TTS_EQUAL(saturated_(eve::div)(Value( 0) , Type(1)), Type(0  ) );
    TTS_EQUAL(saturated_(eve::div)(Value( 1) , Type(1)), Type(1  ) );
    TTS_EQUAL(saturated_(eve::div)(Value(12) , Type(4)), Type(3  ) );
    TTS_EQUAL(saturated_(eve::div)(Value( 1) , Type(2)), Type(0.5) );

    TTS_EQUAL(saturated_(eve::div)(Type( 0) , Value(1)), Type(0  ) );
    TTS_EQUAL(saturated_(eve::div)(Type( 1) , Value(1)), Type(1  ) );
    TTS_EQUAL(saturated_(eve::div)(Type(12) , Value(4)), Type(3  ) );
    TTS_EQUAL(saturated_(eve::div)(Type( 1) , Value(2)), Type(0.5) );
  }
}
