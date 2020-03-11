//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr_abs.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::sqr_abs return type")
{
  TTS_EXPR_IS(eve::sqr_abs(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::sqr_abs behavior")
{
  TTS_EQUAL(eve::sqr_abs(EVE_TYPE(1))               , (EVE_TYPE(1)) );
  TTS_EQUAL(eve::sqr_abs(EVE_TYPE(2))               , (EVE_TYPE(4)) );
  TTS_EQUAL(eve::sqr_abs(eve::Mzero<EVE_TYPE>())    , (EVE_TYPE(0)) );
  TTS_EQUAL(eve::sqr_abs(static_cast<EVE_TYPE>(-2)) , (EVE_TYPE(4)) );
}
