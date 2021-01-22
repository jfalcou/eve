//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/cauchy.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check diff  eve::cauchy return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::diff_1st(eve::cauchy)(T(0), T(0), T(0)), T);
  TTS_EXPR_IS(eve::diff_2nd(eve::cauchy)(T(0), T(0), T(0)), T);
  TTS_EXPR_IS(eve::diff_3rd(eve::cauchy)(T(0), T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::cauchy behavior", EVE_TYPE)
{

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::inf(eve::as<T>());
    auto minf = eve::minf(eve::as<T>());

    TTS_ULP_EQUAL(eve::diff_1st(eve::cauchy)(inf , T(1.), T(4)) , T(0) , 0.5);
    TTS_ULP_EQUAL(eve::diff_1st(eve::cauchy)(inf , T(-1.), T(2)), T(0) , 0.5);
    TTS_ULP_EQUAL(eve::diff_1st(eve::cauchy)(minf, T(1.), T(4)) , T(0) , 0.5);
    TTS_ULP_EQUAL(eve::diff_1st(eve::cauchy)(minf, T(-1.), T(2)), T(0) , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::diff_1st(eve::cauchy)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(eve::diff_1st(eve::cauchy)(T(0))                 , eve::pi(eve::as<T>())  , 0.5);
  TTS_ULP_EQUAL(eve::diff_1st(eve::cauchy)(T(1), T(1))           , eve::pi(eve::as<T>())  , 0.5);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::cauchy)(T(1), T(1))           , -eve::pi(eve::as<T>())  , 0.5);
  TTS_ULP_EQUAL(eve::diff_3rd(eve::cauchy)(T(1), T(1), T(2))     , T(0)  , 1);
}
