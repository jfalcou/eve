//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/j1.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::j1 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::j1(T(0)), T);
}

TTS_CASE_TPL("Check eve::j1 behavior", EVE_TYPE)
{

  auto eve__j1 =  [](auto x) { return eve::j1(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__j1(eve::minf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__j1(eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__j1(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  TTS_ULP_EQUAL(eve__j1(T(20)), T( 6.683312417584991e-02), 11);
  TTS_ULP_EQUAL(eve__j1(T(10)), T( 4.347274616886149e-02), 8);
  TTS_ULP_EQUAL(eve__j1(T(5)), T( -3.275791375914651e-01), 1.5);
  TTS_ULP_EQUAL(eve__j1(T(2)), T( 5.767248077568736e-01), 1);
  TTS_ULP_EQUAL(eve__j1(T(1)), T(4.400505857449336e-01), 0.5);
  TTS_ULP_EQUAL(eve__j1(T(0)), T(0), 0);
}
