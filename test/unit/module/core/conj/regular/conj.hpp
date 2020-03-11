//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/conj.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::conj return type")
{
  TTS_EXPR_IS(eve::conj(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::conj behavior")
{
  TTS_ULP_EQUAL(eve::conj(EVE_TYPE(1)), (EVE_TYPE)(1), 0.5);
}
