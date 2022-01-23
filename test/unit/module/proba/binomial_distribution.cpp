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

EVE_TEST_TYPES("Check eve::binomial_distribution behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  {
    auto bino = eve::binomial_distribution{T(4), T(0.25)};
    TTS_ULP_EQUAL(eve::median(bino)               , T(1.0)  , 0);
    TTS_ULP_EQUAL(eve::mean(bino)                 , T(1.0)  , 0);
    TTS_ULP_EQUAL(eve::mode(bino)                 , T(1.0)  , 0);
    TTS_ULP_EQUAL(eve::var(bino)                  , T(0.75)  , 0);
    TTS_ULP_EQUAL(eve::stdev(bino)                , T(8.660254037844386e-01)  , 0);
    TTS_ULP_EQUAL(eve::cdf(bino, T(0.0))          , T(3.1640625e-01)   , 2.0);
    TTS_ULP_EQUAL(eve::pmf(bino, T(1.0))          , T(1.0546875e-3)   , 1.0);
  }
  {
    auto bino = eve::binomial_distribution{eve::one, T(0.25)};
    TTS_ULP_EQUAL(eve::median(bino)               , T(0.0)  , 0);
    TTS_ULP_EQUAL(eve::mean(bino)                 , T(0.25)  , 0);
    TTS_ULP_EQUAL(eve::mode(bino)                 , T(0.0)  , 0);
    TTS_ULP_EQUAL(eve::var(bino)                  , T(1.875e-01)  , 0);
    TTS_ULP_EQUAL(eve::stdev(bino)                , T(4.330127018922193e-01)  , 0);
    TTS_ULP_EQUAL(eve::cdf(bino, T(0.0))          , T(0.75)   , 1.0);
    TTS_ULP_EQUAL(eve::pmf(bino, T(1.0))          , T(0.25)   , 1.0);
  }
  {
    auto bino = eve::binomial_distribution{T(4), eve::half};
    TTS_ULP_EQUAL(eve::median(bino)               , T(2.0)  , 0);
    TTS_ULP_EQUAL(eve::mean(bino)                 , T(2.0)  , 0);
    TTS_ULP_EQUAL(eve::mode(bino)                 , T(2.0)  , 0);
    TTS_ULP_EQUAL(eve::var(bino)                  , T(1.0)  , 0);
    TTS_ULP_EQUAL(eve::stdev(bino)                , T(1.0)  , 0);
    TTS_ULP_EQUAL(eve::cdf(bino, T(0.0))          , T(0.0625)   , 1.0);
    TTS_ULP_EQUAL(eve::pmf(bino, T(1.0))          , T(1.041666666666667e-02)   , 1.0);
  }
  {
    auto bino = eve::bernouilli<T>;
    TTS_ULP_EQUAL(eve::median(bino)               , T(0.0)  , 0);
    TTS_ULP_EQUAL(eve::mean(bino)                 , T(0.5)  , 0);
    TTS_ULP_EQUAL(eve::mode(bino)                 , T(0.0)  , 0);
    TTS_ULP_EQUAL(eve::var(bino)                  , T(0.25)  , 0);
    TTS_ULP_EQUAL(eve::stdev(bino)                , T(0.5)  , 0);
    TTS_ULP_EQUAL(eve::cdf(bino, T(0.0))          , T(0.5)   , 1.0);
    TTS_ULP_EQUAL(eve::pmf(bino, T(1.0))          , T(0.5)   , 1.0);
  }
};
