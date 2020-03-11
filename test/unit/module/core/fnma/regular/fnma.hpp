//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fnma.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::fnma return type")
{
  TTS_EXPR_IS(eve::fnma(EVE_TYPE(), EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::fnma behavior")
{
  TTS_EQUAL(eve::fnma(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::fnma(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(7)), (EVE_TYPE(7)));
  TTS_EQUAL(eve::fnma(EVE_TYPE(2), EVE_TYPE(0), EVE_TYPE(7)), (EVE_TYPE(7)));
  TTS_EQUAL(eve::fnma(EVE_TYPE(0), EVE_TYPE(5), EVE_TYPE(7)), (EVE_TYPE(7)));
  TTS_EQUAL(eve::fnma(EVE_TYPE(2), EVE_TYPE(5), EVE_TYPE(7)), static_cast<EVE_TYPE>(-3));
}
