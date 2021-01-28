//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exponential.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::exponential behavior", EVE_TYPE)
{
  auto inf  = eve::inf(eve::as<T>());

  auto ex = eve::exponential{T(2.0)};
  TTS_ULP_EQUAL(eve::median(ex)  , T(eve::log_2(eve::as<T>())/2)  , 0.5);
  TTS_ULP_EQUAL(eve::mean  (ex)  , T(0.5)   , 0.5);
  TTS_ULP_EQUAL(eve::var   (ex)  , T(0.25)   , 0.5);
  TTS_ULP_EQUAL(eve::stdev (ex)  , T(0.5)   , 0.5);
  TTS_ULP_EQUAL(eve::cdf(ex, T(1.0))   , T(8.646647167633873e-01)   , 0.5);
  TTS_ULP_EQUAL(eve::pdf(ex, T(1.0))  , T(2.706705664732254e-01)   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ex, T(0.0))  , T(0)   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ex, T(1.0))  , inf    , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ex, T(0.5))  , T(3.465735902799726e-01)    , 0.5);
}

TTS_CASE_TPL("Check eve::exponential behavior", EVE_TYPE)
{
  using elt_t =  eve::element_type_t<T>;

  auto inf  = eve::inf(eve::as<T>());

  auto ex = eve::exponential{T(2.0)};
  TTS_ULP_EQUAL(eve::median(ex)  , T(eve::log_2(eve::as<T>())/2)  , 0.5);
  TTS_ULP_EQUAL(eve::mean  (ex)  , T(0.5)   , 0.5);
  TTS_ULP_EQUAL(eve::var   (ex)  , T(0.25)   , 0.5);
  TTS_ULP_EQUAL(eve::stdev (ex)  , T(0.5)   , 0.5);
  TTS_ULP_EQUAL(eve::cdf(ex, elt_t(1.0))   , T(8.646647167633873e-01)   , 0.5);
  TTS_ULP_EQUAL(eve::pdf(ex, elt_t(1.0))  , T(2.706705664732254e-01)   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ex, elt_t(0.0))  , T(0)   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ex, elt_t(1.0))  , inf    , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ex, elt_t(0.5))  , T(3.465735902799726e-01)    , 0.5);
}


TTS_CASE_TPL("Check eve::exponential behavior", EVE_TYPE)
{
  auto inf  = eve::inf(eve::as<T>());

  auto ex = eve::exponential_1<T>;
  TTS_ULP_EQUAL(eve::median(ex)  , T(eve::log_2(eve::as<T>()))  , 0.5);
  TTS_ULP_EQUAL(eve::mean  (ex)  , T(1)   , 0.5);
  TTS_ULP_EQUAL(eve::var   (ex)  , T(1)   , 0.5);
  TTS_ULP_EQUAL(eve::stdev (ex)  , T(1)   , 0.5);
  TTS_ULP_EQUAL(eve::cdf(ex, T(1.0))   , T(6.321205588285577e-01)   , 0.5);
  TTS_ULP_EQUAL(eve::pdf(ex, T(1.0))  , T(3.678794411714423e-01)   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ex, T(0.0))  , T(0)   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ex, T(1.0))  , inf    , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ex, T(0.5))  , T(0.69314718055994530942)    , 0.5);
}
