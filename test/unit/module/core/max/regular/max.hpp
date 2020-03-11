//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/max.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::max return type")
{
  TTS_EXPR_IS(eve::max(EVE_TYPE(0)  , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::max(EVE_VALUE(0) , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::max(EVE_TYPE(0)  , EVE_VALUE(0)) , (EVE_TYPE));
}

TTS_CASE("Check eve::max behavior")
{
  TTS_EQUAL(eve::max((EVE_TYPE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::max((EVE_TYPE(0)), (EVE_TYPE(1))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::max((EVE_TYPE(1)), (EVE_TYPE(0))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::max((EVE_TYPE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::max((EVE_VALUE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::max((EVE_VALUE(0)), (EVE_TYPE(1))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::max((EVE_VALUE(1)), (EVE_TYPE(0))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::max((EVE_VALUE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::max((EVE_TYPE(0)), (EVE_VALUE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::max((EVE_TYPE(0)), (EVE_VALUE(1))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::max((EVE_TYPE(1)), (EVE_VALUE(0))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::max((EVE_TYPE(1)), (EVE_VALUE(1))), (EVE_TYPE(1)));
}
