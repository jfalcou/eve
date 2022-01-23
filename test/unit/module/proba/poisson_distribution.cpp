//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/proba.hpp>
#include <eve/platform.hpp>
#include <cmath>

EVE_TEST_TYPES("Check eve::poisson_distribution behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  {
    auto ex = eve::poisson_distribution{T(2.0)};
    TTS_ULP_EQUAL(eve::median(ex)  , T(2)  , 0.5);
    TTS_ULP_EQUAL(eve::mean  (ex)  , T(2)   , 0.5);
    TTS_ULP_EQUAL(eve::mode  (ex)  , T(1)   , 0.5);
    TTS_ULP_EQUAL(eve::var   (ex)  , T(2)   , 0.5);
    TTS_ULP_EQUAL(eve::stdev (ex)  , T(eve::sqrt_2(eve::as<T>()))   , 0.5);
    TTS_ULP_EQUAL(eve::cdf(ex, T(1.0))   , T( 5.939941502901619e-01)   , 3.5);
    TTS_ULP_EQUAL(eve::cdf(ex, T(10.0))   , T(9.997995795905170e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::pmf(ex, T(1.0))   , T(2.706705664732254e-01)   , 0.5);
  }
  {
    auto ex = eve::poisson_distribution_1<T>;
    TTS_ULP_EQUAL(eve::median(ex)  , T(1)  , 0.5);
    TTS_ULP_EQUAL(eve::mean  (ex)  , T(1)   , 0.5);
    TTS_ULP_EQUAL(eve::mode  (ex)  , T(0)   , 0.5);
    TTS_ULP_EQUAL(eve::var   (ex)  , T(1)   , 0.5);
    TTS_ULP_EQUAL(eve::stdev (ex)  , T(1)   , 0.5);
    TTS_ULP_EQUAL(eve::cdf(ex, T(1.0))   , T(8.646647167633873e-01)   , 3.5);
    TTS_ULP_EQUAL(eve::cdf(ex, T(10.0))   , T(9.999832982992097e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::pmf(ex, T(1.0))   , T(1)   , 0.5);
  }
};
