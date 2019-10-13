//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/conj.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::conj return type")
{
  TTS_EXPR_IS(eve::conj(Type(0)), (Type));
}

TTS_CASE("Check eve::conj behavior")
{
  TTS_ULP_EQUAL(eve::conj(Type(1)), (Type)(1), 0.5);
}
