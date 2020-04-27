//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fms.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::fms return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::fms(T(), T(), T()), T);
}

TTS_CASE_TPL("Check eve::fms behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::fms(T(0), T(0), T(0)), (T(0)));
  TTS_EQUAL(eve::fms(T(2), T(5), T(7)), (T(3)));
  TTS_EQUAL(eve::fms(T(8), T(5), T(7)), (T(33)));
}

