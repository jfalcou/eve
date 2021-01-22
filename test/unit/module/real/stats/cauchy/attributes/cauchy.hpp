//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cauchy.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::cauchy return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cauchy(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::cauchy behavior", EVE_TYPE)
{
  auto inf  = eve::inf(eve::as<T>());
  auto nan  = eve::nan(eve::as<T>());

  TTS_ULP_EQUAL(eve::median(eve::cauchy)(T(1.0), T(2.0))  , T(1)  , 0.5);
  TTS_ULP_EQUAL(eve::scale (eve::cauchy)(T(1.0), T(2.0))  , T(2)  , 0.5);
  TTS_ULP_EQUAL(eve::mean  (eve::cauchy)(T(1.0), T(2.0))  , inf   , 0.5);
  TTS_ULP_EQUAL(eve::var   (eve::cauchy)(T(1.0), T(2.0))  , nan   , 0.5);
  TTS_ULP_EQUAL(eve::stdev (eve::cauchy)(T(1.0), T(2.0))  , nan   , 0.5);
  auto c_cdf =  eve::cdf(eve::cauchy)(T(1.0), T(2.0));
  TTS_ULP_EQUAL(c_cdf(T(0.0))  , eve::cauchy(T(0.0), T(1.0), T(2.0))   , 0.5);
  auto c_pdf =  eve::pdf(eve::cauchy)(T(1.0), T(2.0));
  TTS_ULP_EQUAL(c_pdf(T(0.0))  , eve::diff(eve::cauchy)(T(0.0), T(1.0), T(2.0))   , 0.5);
  auto c_invcdf =  eve::invcdf(eve::cauchy)(T(0.0), T(1.0));
  TTS_ULP_EQUAL(c_invcdf(T(0.0))  , -inf   , 0.5);
  TTS_ULP_EQUAL(c_invcdf(T(1.0))  , inf    , 0.5);
  TTS_ULP_EQUAL(c_invcdf(T(0.5))  , T(0)    , 0.5);

  TTS_ULP_EQUAL(eve::median(eve::cauchy)(T(1.0))  , T(1)  , 0.5);
  TTS_ULP_EQUAL(eve::scale(eve::cauchy)(T(1.0))  , T(1)  , 0.5);
  TTS_ULP_EQUAL(eve::median(eve::cauchy)(eve::as<T>())  , T(0)  , 0.5);
  TTS_ULP_EQUAL(eve::scale(eve::cauchy)( eve::as<T>())  , T(1)  , 0.5);
}
