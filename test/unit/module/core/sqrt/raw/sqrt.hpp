//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqrt.hpp>
#include <eve/function/raw.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::raw_(eve::sqrt) return type", EVE_TYPE)
{
  TTS_EXPR_IS( eve::raw_(eve::sqrt)(T(0)), T);
}

TTS_CASE_TPL("Check eve::sqrt behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::raw_(eve::sqrt)(T(-0.)), T(0));
  TTS_EQUAL(eve::raw_(eve::sqrt)(T( 0 )), T(0));
  TTS_EQUAL(eve::raw_(eve::sqrt)(T( 1 )), T(1));
  TTS_EQUAL(eve::raw_(eve::sqrt)(T( 4 )), T(2));

  TTS_ULP_EQUAL(eve::raw_(eve::sqrt)(T(2)), eve::sqrt_2(eve::as<T>()), 0.5);
}
