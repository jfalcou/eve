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
#include <eve/constant/half.hpp>


TTS_CASE("Check eve::sinhc return type")
{
  TTS_EXPR_IS(eve::sinhc(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::sinhc behavior")
{
  TTS_ULP_EQUAL(eve::sinhc(EVE_TYPE(0)), EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL(eve::sinhc(EVE_TYPE(1)), eve::sinh(EVE_TYPE(1)), 0.5);
  TTS_ULP_EQUAL(eve::sinhc(EVE_TYPE(2)), eve::sinh(EVE_TYPE(2))*eve::half(eve::as<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL(eve::sinhc(EVE_TYPE(-1)), eve::sinh(EVE_TYPE(1)), 0.5);
}
