//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/clamp.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::clamp return type")
{
  TTS_EXPR_IS(eve::clamp(EVE_TYPE(), EVE_TYPE() , EVE_TYPE()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::clamp(EVE_TYPE(), EVE_VALUE(), EVE_TYPE()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::clamp(EVE_TYPE(), EVE_TYPE() , EVE_VALUE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::clamp(EVE_TYPE(), EVE_VALUE(), EVE_VALUE()), (EVE_TYPE));
}

TTS_CASE("Check eve::clamp behavior")
{
  TTS_EQUAL(eve::clamp(EVE_TYPE(1), EVE_TYPE(2) , EVE_TYPE(4))  , EVE_TYPE(2));
  TTS_EQUAL(eve::clamp(EVE_TYPE(1), EVE_VALUE(2), EVE_TYPE(4))  , EVE_TYPE(2));
  TTS_EQUAL(eve::clamp(EVE_TYPE(1), EVE_TYPE(2) , EVE_VALUE(4)) , EVE_TYPE(2));
  TTS_EQUAL(eve::clamp(EVE_TYPE(1), EVE_VALUE(2), EVE_VALUE(4)) , EVE_TYPE(2));

  TTS_EQUAL(eve::clamp(EVE_TYPE(2), EVE_TYPE(2), EVE_TYPE(4)), EVE_TYPE(2));
  TTS_EQUAL(eve::clamp(EVE_TYPE(2), EVE_VALUE(2), EVE_TYPE(4)), EVE_TYPE(2));
  TTS_EQUAL(eve::clamp(EVE_TYPE(2), EVE_TYPE(2), EVE_VALUE(4)), EVE_TYPE(2));
  TTS_EQUAL(eve::clamp(EVE_TYPE(2), EVE_VALUE(2), EVE_VALUE(4)), EVE_TYPE(2));

  TTS_EQUAL(eve::clamp(EVE_TYPE(3), EVE_TYPE(2), EVE_TYPE(4)), EVE_TYPE(3));
  TTS_EQUAL(eve::clamp(EVE_TYPE(3), EVE_VALUE(2), EVE_TYPE(4)), EVE_TYPE(3));
  TTS_EQUAL(eve::clamp(EVE_TYPE(3), EVE_TYPE(2), EVE_VALUE(4)), EVE_TYPE(3));
  TTS_EQUAL(eve::clamp(EVE_TYPE(3), EVE_VALUE(2), EVE_VALUE(4)), EVE_TYPE(3));

  TTS_EQUAL(eve::clamp(EVE_TYPE(4), EVE_TYPE(2), EVE_TYPE(4)), EVE_TYPE(4));
  TTS_EQUAL(eve::clamp(EVE_TYPE(4), EVE_VALUE(2), EVE_TYPE(4)), EVE_TYPE(4));
  TTS_EQUAL(eve::clamp(EVE_TYPE(4), EVE_TYPE(2), EVE_VALUE(4)), EVE_TYPE(4));
  TTS_EQUAL(eve::clamp(EVE_TYPE(4), EVE_VALUE(2), EVE_VALUE(4)), EVE_TYPE(4));

  TTS_EQUAL(eve::clamp(EVE_TYPE(5), EVE_TYPE(2), EVE_TYPE(4)), EVE_TYPE(4));
  TTS_EQUAL(eve::clamp(EVE_TYPE(5), EVE_VALUE(2), EVE_TYPE(4)), EVE_TYPE(4));
  TTS_EQUAL(eve::clamp(EVE_TYPE(5), EVE_TYPE(2), EVE_VALUE(4)), EVE_TYPE(4));
  TTS_EQUAL(eve::clamp(EVE_TYPE(5), EVE_VALUE(2), EVE_VALUE(4)), EVE_TYPE(4));
}
