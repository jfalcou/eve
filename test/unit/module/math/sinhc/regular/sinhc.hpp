//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinhc.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/half.hpp>


TTS_CASE_TPL("Check eve::sinhc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinhc(T(0)), T);
}

TTS_CASE_TPL("Check eve::sinhc behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::sinhc(T(0)), T(1), 0.5);
  TTS_ULP_EQUAL(eve::sinhc(T(1)), eve::sinh(T(1)), 0.5);
  TTS_ULP_EQUAL(eve::sinhc(T(2)), eve::sinh(T(2))*eve::Half<T>(), 0.5);
  TTS_ULP_EQUAL(eve::sinhc(T(-1)), eve::sinh(T(1)), 0.5);
}
