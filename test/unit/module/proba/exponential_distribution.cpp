//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/proba.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::exponential_distribution behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(tts::type<T>)
{
  using elt_t =  eve::element_type_t<T>;
  auto inf  = eve::inf(eve::as<T>());
  {
    auto ex = eve::exponential_distribution{T(2.0)};
    TTS_ULP_EQUAL(eve::median(ex)  , T(eve::log_2(eve::as<T>())/2)  , 0.5);
    TTS_ULP_EQUAL(eve::mean  (ex)  , T(0.5)   , 0.5);
    TTS_ULP_EQUAL(eve::mode  (ex)  , T(0.0)   , 0.5);
    TTS_ULP_EQUAL(eve::var   (ex)  , T(0.25)   , 0.5);
    TTS_ULP_EQUAL(eve::stdev (ex)  , T(0.5)   , 0.5);
    TTS_ULP_EQUAL(eve::cdf(ex, T(1.0))   , T(8.646647167633873e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(ex, T(1.0))  , T(2.706705664732254e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ex, T(0.0))  , T(0)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ex, T(1.0))  , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ex, T(0.5))  , T(3.465735902799726e-01)    , 0.5);
  }
  {
    auto ex = eve::exponential_distribution{T(2.0)};
    TTS_ULP_EQUAL(eve::median(ex)  , T(eve::log_2(eve::as<T>())/2)  , 0.5);
    TTS_ULP_EQUAL(eve::mean  (ex)  , T(0.5)   , 0.5);
    TTS_ULP_EQUAL(eve::mode  (ex)  , T(0.0)   , 0.5);
    TTS_ULP_EQUAL(eve::var   (ex)  , T(0.25)   , 0.5);
    TTS_ULP_EQUAL(eve::stdev (ex)  , T(0.5)   , 0.5);
    TTS_ULP_EQUAL(eve::cdf(ex, elt_t(1.0))   , T(8.646647167633873e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(ex, elt_t(1.0))  , T(2.706705664732254e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ex, elt_t(0.0))  , T(0)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ex, elt_t(1.0))  , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ex, elt_t(0.5))  , T(3.465735902799726e-01)    , 0.5);
  }
  {
    auto ex = eve::exponential_distribution_1<T>;
    TTS_ULP_EQUAL(eve::median(ex)  , T(eve::log_2(eve::as<T>()))  , 0.5);
    TTS_ULP_EQUAL(eve::mean  (ex)  , T(1)   , 0.5);
    TTS_ULP_EQUAL(eve::mode  (ex)  , T(0.0)   , 0.5);
    TTS_ULP_EQUAL(eve::var   (ex)  , T(1)   , 0.5);
    TTS_ULP_EQUAL(eve::stdev (ex)  , T(1)   , 0.5);
    TTS_ULP_EQUAL(eve::cdf(ex, T(1.0))   , T(6.321205588285577e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(ex, T(1.0))  , T(3.678794411714423e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ex, T(0.0))  , T(0)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ex, T(1.0))  , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ex, T(0.5))  , T(0.69314718055994530942)    , 0.5);
  }
};
