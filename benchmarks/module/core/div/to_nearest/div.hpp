//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mone.hpp>
#include <type_traits>

TTS_CASE("Check div return type")
{
  TTS_EXPR_IS(eve::div(EVE_TYPE(), EVE_TYPE() , eve::to_nearest_), (EVE_TYPE));
  TTS_EXPR_IS(eve::div(EVE_TYPE(), EVE_VALUE() , eve::to_nearest_), (EVE_TYPE));
  TTS_EXPR_IS(eve::div(EVE_VALUE(), EVE_TYPE() , eve::to_nearest_), (EVE_TYPE));
}

TTS_CASE("Check eve::div behavior")
{
  if constexpr(std::is_integral_v<EVE_VALUE> && std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::div(eve::Mone<EVE_TYPE>()  , EVE_TYPE{2} , eve::to_nearest_), EVE_TYPE(0));
    TTS_EQUAL(eve::div(eve::Mone<EVE_VALUE>() , EVE_TYPE{2} , eve::to_nearest_), EVE_TYPE(0));
    TTS_EQUAL(eve::div(eve::Mone<EVE_TYPE>()  , EVE_VALUE{2}, eve::to_nearest_), EVE_TYPE(0));
  }
  TTS_EQUAL(eve::div(EVE_TYPE{12}, EVE_TYPE{4}, eve::to_nearest_), EVE_TYPE{3});
  TTS_EQUAL(eve::div(EVE_TYPE{1} , EVE_TYPE{2}, eve::to_nearest_), EVE_TYPE(0));
  TTS_EQUAL(eve::div(EVE_TYPE{3} , EVE_TYPE{2}, eve::to_nearest_), EVE_TYPE(2));
  TTS_EQUAL(eve::div(EVE_TYPE{4} , EVE_TYPE{3}, eve::to_nearest_), EVE_TYPE(1));

  TTS_EQUAL(eve::div(EVE_VALUE{12}, EVE_TYPE{4}, eve::to_nearest_), EVE_TYPE{3});
  TTS_EQUAL(eve::div(EVE_VALUE{1} , EVE_TYPE{2}, eve::to_nearest_), EVE_TYPE(0));
  TTS_EQUAL(eve::div(EVE_VALUE{3} , EVE_TYPE{2}, eve::to_nearest_), EVE_TYPE(2));
  TTS_EQUAL(eve::div(EVE_VALUE{4} , EVE_TYPE{3}, eve::to_nearest_), EVE_TYPE(1));

  TTS_EQUAL(eve::div(EVE_TYPE{12}, EVE_VALUE{4}, eve::to_nearest_), EVE_TYPE{3});
  TTS_EQUAL(eve::div(EVE_TYPE{1} , EVE_VALUE{2}, eve::to_nearest_), EVE_TYPE(0));
  TTS_EQUAL(eve::div(EVE_TYPE{3} , EVE_VALUE{2}, eve::to_nearest_), EVE_TYPE(2));
  TTS_EQUAL(eve::div(EVE_TYPE{4} , EVE_VALUE{3}, eve::to_nearest_), EVE_TYPE(1));
}
