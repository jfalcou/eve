//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::cyl_bessel_j0 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cyl_bessel_j0(T(0)), T);
}

TTS_CASE_TPL("Check eve::cyl_bessel_j0 behavior", EVE_TYPE)
{

  auto eve__cyl_bessel_j0 =  [](auto x) { return eve::cyl_bessel_j0(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_j0(eve::minf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_j0(eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_j0(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(T(10)), T( -2.459357644513482e-01), 2.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(T(5)), T(-1.775967713143384e-01), 1.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(T(2)), T( 2.238907791412356e-01), 0.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(T(1)), T( 7.651976865579666e-01), 0.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(T(0)), T(1), 0);
}
