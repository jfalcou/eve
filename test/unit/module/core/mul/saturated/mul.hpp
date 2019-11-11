//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check saturated_(eve::mul) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::mul)(Type(), Type()), (Type));
}

TTS_CASE("Check saturated_(eve::mul) behavior")
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
      TTS_EQUAL(saturated_(eve::mul)(tvmin       , (Type(-2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)(tvmax       , (Type(-2))), tvmin);
      TTS_EQUAL(saturated_(eve::mul)((Type(-1))  , (Type( 0))), Type(0));
      TTS_EQUAL(saturated_(eve::mul)(tvmax       ,      tvmax), tvmax);
      TTS_EQUAL(saturated_(eve::mul)(tvmax       ,      tvmin), tvmin);

      TTS_EQUAL(saturated_(eve::mul)(vmax       , (Type(-2))), tvmin);
      TTS_EQUAL(saturated_(eve::mul)(vmin       , (Type(-2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((Value(-1)), (Type( 0))), Type(0));
      TTS_EQUAL(saturated_(eve::mul)(vmax       ,      tvmax), tvmax);
      TTS_EQUAL(saturated_(eve::mul)(vmax       ,      tvmin), tvmin);

      TTS_EQUAL(saturated_(eve::mul)(tvmax       , (Value(-2))), tvmin);
      TTS_EQUAL(saturated_(eve::mul)(tvmin       , (Value(-2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((Type(-1))  , (Value( 0))), Type(0));
      TTS_EQUAL(saturated_(eve::mul)(tvmax       ,        vmax), tvmax);
      TTS_EQUAL(saturated_(eve::mul)(tvmax       ,        vmin), tvmin);

    }
    else
    {
      TTS_EQUAL(saturated_(eve::mul)(tvmax    , (Type(2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((Type(2)), tvmax)    , tvmax);

      TTS_EQUAL(saturated_(eve::mul)(vmax      , (Type(2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((Value(2)), tvmax)    , tvmax);

      TTS_EQUAL(saturated_(eve::mul)(tvmax     , (Value(2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((Type(2)) , vmax )     , tvmax);

    }
  }
  else
  {
    TTS_EQUAL(saturated_(eve::mul)(Type( 0) , Type(1)), Type(0  ) );
    TTS_EQUAL(saturated_(eve::mul)(Type( 1) , Type(1)), Type(1  ) );
    TTS_EQUAL(saturated_(eve::mul)(Type(12) , Type(4)), Type(48  ) );

    TTS_EQUAL(saturated_(eve::mul)(Value( 0) , Type(1)), Type(0  ) );
    TTS_EQUAL(saturated_(eve::mul)(Value( 1) , Type(1)), Type(1  ) );
    TTS_EQUAL(saturated_(eve::mul)(Value(12) , Type(4)), Type(48  ) );

    TTS_EQUAL(saturated_(eve::mul)(Type( 0) , Value(1)), Type(0  ) );
    TTS_EQUAL(saturated_(eve::mul)(Type( 1) , Value(1)), Type(1  ) );
    TTS_EQUAL(saturated_(eve::mul)(Type(12) , Value(4)), Type(48  ) );
  }
}
