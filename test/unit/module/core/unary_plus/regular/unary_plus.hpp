//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/unary_plus.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::unary_plus return type")
{
  TTS_EXPR_IS(eve::unary_plus(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::unary_plus behavior")
{
  TTS_EQUAL(eve::unary_plus(EVE_TYPE(1)), (EVE_TYPE(1)));
}
