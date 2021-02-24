//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinhc.hpp>
#include <eve/constant/half.hpp>


TTS_CASE_TPL("Check eve::sinhc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinhc(T(0)), T);
}

TTS_CASE_TPL("Check eve::sinhc behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::sinhc(T(0)), T(1), 0.5);
  TTS_ULP_EQUAL(eve::sinhc(T(1)), eve::sinh(T(1)), 0.5);
  TTS_ULP_EQUAL(eve::sinhc(T(2)), eve::sinh(T(2))*eve::half(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::sinhc(T(-1)), eve::sinh(T(1)), 0.5);
}
