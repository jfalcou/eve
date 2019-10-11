//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/unary_plus.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::unary_plus return type")
{
  TTS_EXPR_IS(eve::unary_plus(Type()), (Type));
}

TTS_CASE("Check eve::unary_plus behavior")
{
  TTS_EQUAL(eve::unary_plus(Type(1)), (Type(1)));
}
