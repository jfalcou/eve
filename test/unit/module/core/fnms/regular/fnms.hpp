//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fnms.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::fnms return type")
{
  TTS_EXPR_IS(eve::fnms(EVE_TYPE(), EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::fnms behavior")
{
  TTS_EQUAL(eve::fnms(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::fnms(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(7)), static_cast<EVE_TYPE>(-7));
  TTS_EQUAL(eve::fnms(EVE_TYPE(2), EVE_TYPE(0), EVE_TYPE(7)), static_cast<EVE_TYPE>(-7));
  TTS_EQUAL(eve::fnms(EVE_TYPE(0), EVE_TYPE(5), EVE_TYPE(7)), static_cast<EVE_TYPE>(-7));
  TTS_EQUAL(eve::fnms(EVE_TYPE(2), EVE_TYPE(5), EVE_TYPE(7)), static_cast<EVE_TYPE>(-17));
}
