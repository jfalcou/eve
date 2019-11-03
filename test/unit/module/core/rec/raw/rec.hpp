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
#include <eve/function/raw.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::raw_(eve::raw_(eve::rec)) return type")
{
  TTS_EXPR_IS(eve::raw_(eve::rec)(Type(0)), (Type));
}

TTS_CASE("Check eve::raw_(eve::rec) behavior")
{
  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_RELATIVE_EQUAL(eve::raw_(eve::rec)( Type(1)) , (Type(1))     , 0.2);
    TTS_RELATIVE_EQUAL(eve::raw_(eve::rec)( Type(47)), (Type(1./47.)), 0.2);
  }
  else
  {
    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::raw_(eve::rec)(Type(- 1)), (Type(-1)));
      TTS_EQUAL(eve::raw_(eve::rec)(Type(-47)), (Type( 0)));
    }
    else
    {
      TTS_EQUAL(eve::raw_(eve::rec)(Type(1)) , (Type(1)));
      TTS_EQUAL(eve::raw_(eve::rec)(Type(47)), (Type(0)));
    }
  }
}
