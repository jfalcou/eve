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

EVE_TEST_TYPES("Check eve::lognormal_distribution behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  auto inf  = eve::inf(eve::as<T>());
  {
    auto lno = eve::lognormal_distribution{T(1.0), T(2.0)};
    TTS_ULP_EQUAL(eve::median(lno)               , T(2.718281828459045235360287471)   , 0.5);
    TTS_ULP_EQUAL(eve::mean(lno)                 , T(20.085536923187667740928529654)  , 0.5);
    TTS_ULP_EQUAL(eve::mode(lno)                 , T(4.978706836786394e-02)  , 0.5);
    TTS_ULP_EQUAL(eve::var(lno)                  , T(21623.0370013139813943)          , 0.5);
    TTS_ULP_EQUAL(eve::stdev(lno)                , T(147.047737151286967345379028091) , 0.5);
    TTS_ULP_EQUAL(eve::cdf(lno, T(0.0))          , T(0.0)   , 0.5);
    TTS_ULP_EQUAL(eve::raw(eve::cdf)(lno, T(0.0)), T(0.0)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(lno, T(1.0))          , T(1.760326633821498e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(lno, T(0.0))       , T(0.0)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(lno, T(1.0))       , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(lno, T(0.5))       , T(2.718281828459045235360287471)   , 0.5);
  }
  {
    auto lno = eve::lognormal_distribution{eve::zero, T(2.0)};
    TTS_ULP_EQUAL(eve::median(lno)               , T(1.0)  , 0.5);
    TTS_ULP_EQUAL(eve::mean(lno)                 , T(7.389056098930650)  , 0.5);
    TTS_ULP_EQUAL(eve::mode(lno)                 , T(1.831563888873418e-02)  , 0.5);
    TTS_ULP_EQUAL(eve::var(lno)                  , T(2926.359837008584)  , 0.5);
    TTS_ULP_EQUAL(eve::stdev(lno)                , T(54.09583936874058)  , 0.5);
    TTS_ULP_EQUAL(eve::cdf(lno, T(1.0))          , T(0.5)   , 1);
    TTS_ULP_EQUAL(eve::raw(eve::cdf)(lno, T(1.0)), T(0.5)   , 1);
    TTS_ULP_EQUAL(eve::pdf(lno, T(1.0))          , T(1.994711402007164e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(lno, T(0.0))       , T(0.0)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(lno, T(1.0))       , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(lno, T(0.5))       , T(1)   , 0.5);
  }
  {
    auto inf  = eve::inf(eve::as<T>());

    auto lno = eve::lognormal_distribution_01<T>;
    TTS_ULP_EQUAL(eve::median(lno)               , T(1.0)                , 0.0);
    TTS_ULP_EQUAL(eve::mean(lno)                 , T(1.648721270700128)  , 0.5);
    TTS_ULP_EQUAL(eve::mode(lno)                 , T(0.367879441171442)  , 0.5);
    TTS_ULP_EQUAL(eve::var(lno)                  , T(4.670774270471604)  , 0.5);
    TTS_ULP_EQUAL(eve::stdev(lno)                , T(2.161197415895088)  , 0.5);
    TTS_ULP_EQUAL(eve::cdf(lno, T(1.0))          , T(0.5)   , 1);
    TTS_ULP_EQUAL(eve::raw(eve::cdf)(lno, T(1.0)), T(0.5)   , 1);
    TTS_ULP_EQUAL(eve::pdf(lno, T(1.0))          , T(3.989422804014327e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(lno, T(0.0))       , T(0.0)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(lno, T(1.0))       , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(lno, T(0.5))       , T(1)   , 0.5);
  }
};
