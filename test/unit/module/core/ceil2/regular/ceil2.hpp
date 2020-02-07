//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ceil2.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check ceil2 return type")
{
  TTS_EXPR_IS(eve::ceil2(Type()), (Type));
}

TTS_CASE("Check eve::ceil2 behavior")
{
  if constexpr(!std::is_floating_point_v<Value>)
  {
    for(Value z = 4; z < eve::Valmax<Value>()/4; z*=2)
    {
      TTS_EQUAL(eve::ceil2(Type(z))    , Type(z));
      TTS_EQUAL(eve::ceil2(Type(z-1))  , Type(z));
      TTS_EQUAL(eve::ceil2(Type(z/2+1)), Type(z));
    }
  }
  else  
  {
    TTS_EQUAL(eve::ceil2(Type(0))  , Type(1));
    TTS_EQUAL(eve::ceil2(Type(1))  , Type(1));
    TTS_EQUAL(eve::ceil2(Type(1.3)), Type(2));
    TTS_EQUAL(eve::ceil2(Type(1.5)), Type(2));
    TTS_EQUAL(eve::ceil2(Type(1.6)), Type(2));
    TTS_EQUAL(eve::ceil2(Type(2.9)), Type(4));
  }
}
