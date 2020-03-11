//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fms.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::fms return type")
{
  TTS_EXPR_IS(eve::fms(EVE_TYPE(), EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::fms behavior")
{
  TTS_EQUAL(eve::fms(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::fms(EVE_TYPE(2), EVE_TYPE(5), EVE_TYPE(7)), (EVE_TYPE(3)));
  TTS_EQUAL(eve::fms(EVE_TYPE(8), EVE_TYPE(5), EVE_TYPE(7)), (EVE_TYPE(33)));
}

