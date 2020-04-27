//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fma.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::fma return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::fma(T(), T(), T()), T);
}

TTS_CASE_TPL("Check eve::fma behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::fma(T(0), T(0), T(0)), (T(0)));
  TTS_EQUAL(eve::fma(T(0), T(0), T(7)), (T(7)));
  TTS_EQUAL(eve::fma(T(2), T(0), T(7)), (T(7)));
  TTS_EQUAL(eve::fma(T(0), T(5), T(7)), (T(7)));
  TTS_EQUAL(eve::fma(T(2), T(5), T(7)), (T(17)));
}
