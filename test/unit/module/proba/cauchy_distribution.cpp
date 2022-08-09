//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/proba.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::cauchy_distribution behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(tts::type<T>)
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
    TTS_ULP_EQUAL(eve::mode(ca)            , T(1.0)  , 0);
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
    TTS_ULP_EQUAL(eve::mode(ca)            , T(0.0)  , 0);
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
    TTS_ULP_EQUAL(eve::mode(ca)            , T(2.0)  , 0);
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
    TTS_ULP_EQUAL(eve::mode(ca)          , T(0.0)  , 0);
    TTS_ULP_EQUAL(eve::scale(ca)           , T(1)  , 0);
    TTS_ULP_EQUAL(eve::fisher(ca)          , T(0.5)  , 0);
  }
};
