//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cauchy_distribution.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/platform.hpp>
#include <cmath>

EVE_TEST_TYPES("Check eve::binomial_distribution behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as_<T>)
{
  auto inf  = eve::inf(eve::as<T>());
  {
    auto ca = eve::cauchy_distribution{T(1.0), T(2.0)};
    TTS_ULP_EQUAL(eve::cdf(ca, T(0.0))     , T(3.524163823495667e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(ca, T(1.0))     , T(1.591549430918953e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(0.0))  , -inf   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(1.0))  , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(0.5))  , T(1)    , 0.5);
    TTS_ULP_EQUAL(eve::median(ca)          , T(1.0)  , 0);
    TTS_ULP_EQUAL(eve::scale(ca)           , T(2.0)  , 0);
    TTS_ULP_EQUAL(eve::fisher(ca)          , T(1/8.0)  , 0);
  }
  {
    auto ca = eve::cauchy_distribution(eve::zero, T(2.0));
    TTS_ULP_EQUAL(eve::cdf(ca, T(0.0))     , T(0.5)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(ca, T(1.0))     , T(1.273239544735163e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(0.0))  , -inf   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(1.0))  , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(0.5))  , T(0)    , 0.5);
    TTS_ULP_EQUAL(eve::median(ca)          , T(0.0)  , 0);
    TTS_ULP_EQUAL(eve::scale(ca)           , T(2.0)  , 0);
    TTS_ULP_EQUAL(eve::fisher(ca)          , T(1/8.0)  , 0);
  }
  {
    auto ca = eve::cauchy_distribution(T(2.0), eve::one);
    TTS_ULP_EQUAL(eve::cdf(ca, T(0.0))     , T(1.475836176504333e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(ca, T(1.0))     , T(1.591549430918953e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(0.0))  , -inf   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(1.0))  , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(0.5))  , T(2)    , 0.5);
    TTS_ULP_EQUAL(eve::median(ca)          , T(2.0)  , 0);
    TTS_ULP_EQUAL(eve::scale(ca)           , T(1.0)  , 0);
    TTS_ULP_EQUAL(eve::fisher(ca)          , T(0.5)  , 0);
  }
  {
    auto ca = eve::cauchy_distribution_01<T>;
    TTS_ULP_EQUAL(eve::cdf(ca, T(0.0))     , T(0.5)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(ca, T(1.0))     , T(1.591549430918953e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(0.0))  , -inf   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(1.0))  , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ca, T(0.5))  , T(0.0)  , 0.5);
    TTS_ULP_EQUAL(eve::median(ca)          , T(0.0)  , 0);
    TTS_ULP_EQUAL(eve::scale(ca)           , T(1)  , 0);
    TTS_ULP_EQUAL(eve::fisher(ca)          , T(0.5)  , 0);
  }
}; 
