//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::rec return type")
{
  TTS_EXPR_IS(eve::rec(Type(0)), (Type));
}

TTS_CASE("Check eve::rec behavior")
{
  if constexpr(std::is_floating_point_v<Value> && eve::platform::supports_infinites)
  {
    TTS_ULP_EQUAL(eve::rec( Type(0)), (eve::Inf<Type>()) , 0.5);
    TTS_ALL_ULP_EQUAL(eve::rec(eve::Mzero<Type>()), (eve::Minf<Type>()), 0.5);
    TTS_ULP_EQUAL(eve::rec( Type(1)), (Type(1))          , 0.5);
    TTS_ULP_EQUAL(eve::rec( Type(2)), (Type(1./2.))      , 0.5);
  }
  else
  {
    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::rec(Type(- 1)), (Type(-1)));
      TTS_EQUAL(eve::rec(Type(-47)), (Type( 0)));
    }
    else
    {
      TTS_EQUAL(eve::rec(Type(1)) , (Type(1)));
      TTS_EQUAL(eve::rec(Type(47)), (Type(0)));
    }
  }
}
