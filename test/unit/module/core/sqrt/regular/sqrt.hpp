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
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::sqrt return type")
{
  TTS_EXPR_IS(eve::sqrt(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::sqrt behavior")
{
  TTS_EQUAL(eve::sqrt(eve::Mzero<EVE_TYPE>()) , (EVE_TYPE(0)));
  TTS_EQUAL(eve::sqrt(EVE_TYPE(0))            , (EVE_TYPE(0)));
  TTS_EQUAL(eve::sqrt(EVE_TYPE(1))            , (EVE_TYPE(1)));
  TTS_EQUAL(eve::sqrt(EVE_TYPE(4))            , (EVE_TYPE(2)));

  TTS_ULP_EQUAL(eve::sqrt(EVE_TYPE(2)), eve::Sqrt_2<EVE_TYPE>(), 0.5);
  TTS_IEEE_EQUAL(eve::sqrt( eve::Nan<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
}
