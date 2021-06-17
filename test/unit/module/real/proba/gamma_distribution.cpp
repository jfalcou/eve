//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/gamma_distribution.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/platform.hpp>

EVE_TEST_TYPES("Check eve::gamma_distribution behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as_<T>)
{
  auto inf  = eve::inf(eve::as<T>());
  {
    auto d = eve::gamma_distribution{T(2.0), T(2.0)};
    TTS_ULP_EQUAL(eve::mean(d)                 , T(4.0)  , 0.5);
    TTS_ULP_EQUAL(eve::var(d)                  , T(8.0)  , 0.5);
    TTS_ULP_EQUAL(eve::stdev(d)                , T(2.828427124746190)  , 0.5);
    TTS_ULP_EQUAL(eve::cdf(d, T(0.0))          , T(0.0)   , 0.5);
    TTS_ULP_EQUAL(eve::cdf(d, T(1.0))          , T(9.020401043104986e-02)   , 5);
    TTS_ULP_EQUAL(eve::pdf(d, T(1.0))          , T(1.516326649281584e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(d, T(0.0))       , T(0)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(d, T(1.0))       , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(d, T(0.5))       , T(3.356693980033322)   , 4.0);
  }
  {
    auto d = eve::gamma_distribution{eve::one, T(2.0)};
    TTS_ULP_EQUAL(eve::mean(d)                 , T(2.0)  , 0.5);
    TTS_ULP_EQUAL(eve::var(d)                  , T(4.0)  , 0.5);
    TTS_ULP_EQUAL(eve::stdev(d)                , T(2.0)  , 0.5);
    TTS_ULP_EQUAL(eve::cdf(d, T(1.0))          , T(3.934693402873666e-01)   , 2.0);
    TTS_ULP_EQUAL(eve::pdf(d, T(1.0))          , T(3.032653298563167e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(d, T(0.0))       , T(0)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(d, T(1.0))       , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(d, T(0.5))       , T(1.386294361119891)   , 1.0);
  }
  {
    auto d = eve::gamma_distribution_11<T>;
    TTS_ULP_EQUAL(eve::mean(d)                 , T(1.0)  , 0.5);
    TTS_ULP_EQUAL(eve::var(d)                  , T(1.0)  , 0.5);
    TTS_ULP_EQUAL(eve::stdev(d)                , T(1.0)  , 0.5);
    TTS_ULP_EQUAL(eve::cdf(d, T(1.0))          , T(6.321205588285577e-01)   , 1);
    TTS_ULP_EQUAL(eve::pdf(d, T(1.0))          , T(3.678794411714423e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(d, T(0.0))       , T(0)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(d, T(1.0))       , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(d, T(0.5))       , T(6.931471805599453e-01)   , 0.5);
  }
};
