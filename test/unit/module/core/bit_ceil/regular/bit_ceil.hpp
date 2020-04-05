//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_ceil.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check bit_ceil return type")
{
  TTS_EXPR_IS(eve::bit_ceil(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::bit_ceil behavior")
{
  if constexpr(!std::is_floating_point_v<EVE_VALUE>)
  {
    for(EVE_VALUE z = 4; z < eve::Valmax<EVE_VALUE>()/4; z*=2)
    {
      TTS_EQUAL(eve::bit_ceil(EVE_TYPE(z))    , EVE_TYPE(z));
      TTS_EQUAL(eve::bit_ceil(EVE_TYPE(z-1))  , EVE_TYPE(z));
      TTS_EQUAL(eve::bit_ceil(EVE_TYPE(z/2+1)), EVE_TYPE(z));
    }
  }
  else  
  {
    TTS_EQUAL(eve::bit_ceil(EVE_TYPE(0))  , EVE_TYPE(1));
    TTS_EQUAL(eve::bit_ceil(EVE_TYPE(1))  , EVE_TYPE(1));
    TTS_EQUAL(eve::bit_ceil(EVE_TYPE(1.3)), EVE_TYPE(2));
    TTS_EQUAL(eve::bit_ceil(EVE_TYPE(1.5)), EVE_TYPE(2));
    TTS_EQUAL(eve::bit_ceil(EVE_TYPE(1.6)), EVE_TYPE(2));
    TTS_EQUAL(eve::bit_ceil(EVE_TYPE(2.9)), EVE_TYPE(4));
  }
}
