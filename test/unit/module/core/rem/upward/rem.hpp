//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mone.hpp>
#include <type_traits>

TTS_CASE("Check rem return type")
{
  TTS_EXPR_IS(eve::rem(EVE_TYPE(), EVE_TYPE() , eve::upward_), (EVE_TYPE));
  TTS_EXPR_IS(eve::rem(EVE_TYPE(), EVE_VALUE() , eve::upward_), (EVE_TYPE));
  TTS_EXPR_IS(eve::rem(EVE_VALUE(), EVE_TYPE() , eve::upward_), (EVE_TYPE));
}

TTS_CASE("Check eve::rem behavior")
{
  if constexpr(std::is_integral_v<EVE_VALUE> && std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::rem(eve::Mone<EVE_TYPE>()  , EVE_TYPE{2} , eve::upward_), EVE_TYPE(-1));
    TTS_EQUAL(eve::rem(eve::Mone<EVE_VALUE>() , EVE_TYPE{2} , eve::upward_), EVE_TYPE(-1));
    TTS_EQUAL(eve::rem(eve::Mone<EVE_TYPE>()  , EVE_VALUE{2}, eve::upward_), EVE_TYPE(-1));
    TTS_EQUAL(eve::rem(EVE_TYPE(-4)  , EVE_TYPE{3} , eve::upward_), EVE_TYPE(-1));
    TTS_EQUAL(eve::rem(EVE_VALUE(-4) , EVE_TYPE{3} , eve::upward_), EVE_TYPE(-1));
    TTS_EQUAL(eve::rem(EVE_TYPE(-4)  , EVE_VALUE{3}, eve::upward_), EVE_TYPE(-1));
  }
  TTS_EQUAL(eve::rem(EVE_TYPE{12}, EVE_TYPE{4}, eve::upward_), EVE_TYPE{0});
  TTS_EQUAL(eve::rem(EVE_TYPE{1} , EVE_TYPE{2}, eve::upward_), EVE_TYPE(-1));
  TTS_EQUAL(eve::rem(EVE_TYPE{4} , EVE_TYPE{3}, eve::upward_), EVE_TYPE(-2));

  TTS_EQUAL(eve::rem(EVE_VALUE{12}, EVE_TYPE{4}, eve::upward_), EVE_TYPE{0});
  TTS_EQUAL(eve::rem(EVE_VALUE{1} , EVE_TYPE{2}, eve::upward_), EVE_TYPE(-1));
  TTS_EQUAL(eve::rem(EVE_VALUE{4} , EVE_TYPE{3}, eve::upward_), EVE_TYPE(-2));

  TTS_EQUAL(eve::rem(EVE_TYPE{12}, EVE_VALUE{4}, eve::upward_), EVE_TYPE{0});
  TTS_EQUAL(eve::rem(EVE_TYPE{1} , EVE_VALUE{2}, eve::upward_), EVE_TYPE(-1));
  TTS_EQUAL(eve::rem(EVE_TYPE{4} , EVE_VALUE{3}, eve::upward_), EVE_TYPE(-2));
}
