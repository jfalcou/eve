//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/normal_distribution.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::normal_distribution behavior", EVE_TYPE)
{
  auto inf  = eve::inf(eve::as<T>());

  auto no = eve::normal_distribution{T(1.0), T(2.0)};
  TTS_ULP_EQUAL(eve::median(no)               , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::mean(no)                 , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::var(no)                  , T(4.0)  , 0);
  TTS_ULP_EQUAL(eve::stdev(no)                , T(2.0)  , 0);
  TTS_ULP_EQUAL(eve::cdf(no, T(0.0))          , T(0.30853753872598689636229538939166226011639782444542)   , 0.5);
  TTS_ULP_EQUAL(eve::raw(eve::cdf)(no, T(0.0)), T(0.30853753872598689636229538939166226011639782444542)   , 0.5);
  TTS_ULP_EQUAL(eve::pdf(no, T(1.0))          , T(0.19947114020071633896997302996719093423792931558246)   , 1.0);
  TTS_ULP_EQUAL(eve::invcdf(no, T(0.0))       , -inf   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(no, T(1.0))       , inf    , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(no, T(0.5))       , T(1)   , 0.5);
}

TTS_CASE_TPL("Check eve::normal_distribution behavior", EVE_TYPE)
{
  auto inf  = eve::inf(eve::as<T>());

  auto no = eve::normal_distribution{eve::zero, T(2.0)};
  TTS_ULP_EQUAL(eve::median(no)               , T(0.0)  , 0);
  TTS_ULP_EQUAL(eve::mean(no)                 , T(0.0)  , 0);
  TTS_ULP_EQUAL(eve::var(no)                  , T(4.0)  , 0);
  TTS_ULP_EQUAL(eve::stdev(no)                , T(2.0)  , 0);
  TTS_ULP_EQUAL(eve::cdf(no, T(-1.0))          , T(0.30853753872598689636229538939166226011639782444542)   , 0.5);
  TTS_ULP_EQUAL(eve::raw(eve::cdf)(no, T(-1.0)), T(0.30853753872598689636229538939166226011639782444542)   , 0.5);
  TTS_ULP_EQUAL(eve::pdf(no, T(0.0))          , T(0.19947114020071633896997302996719093423792931558246)   , 1.0);
  TTS_ULP_EQUAL(eve::invcdf(no, T(0.0))       , -inf   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(no, T(1.0))       , inf    , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(no, T(0.5))       , T(0)   , 0.5);
}

TTS_CASE_TPL("Check eve::normal_distribution behavior", EVE_TYPE)
{
  auto inf  = eve::inf(eve::as<T>());

  auto no = eve::normal_distribution_01<T>;
  TTS_ULP_EQUAL(eve::median(no)               , T(0.0)  , 0);
  TTS_ULP_EQUAL(eve::mean(no)                 , T(0.0)  , 0);
  TTS_ULP_EQUAL(eve::var(no)                  , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::stdev(no)                , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::cdf(no, T(0.0))          , T(0.5)   , 1);
  TTS_ULP_EQUAL(eve::raw(eve::cdf)(no, T(0.0)), T(0.5)   , 1);
  TTS_ULP_EQUAL(eve::pdf(no, T(0.0))          , T(2*0.19947114020071633896997302996719093423792931558246)   , 1.0);
  TTS_ULP_EQUAL(eve::invcdf(no, T(0.0))       , -inf   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(no, T(1.0))       , inf    , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(no, T(0.5))       , T(0)   , 0.5);
}
