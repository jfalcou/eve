//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/ev_distribution.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/platform.hpp>


EVE_TEST_TYPES("Check eve::ev_distribution behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  auto inf  = eve::inf(eve::as<T>());
  {
    auto ev = eve::ev_distribution{T(1.0), T(2.0)};
    TTS_ULP_EQUAL(eve::median(ev)               , T(1.733025841163329)   , 1.0);
    TTS_ULP_EQUAL(eve::mean(ev)                 , T(2.154431329803066)   , 0.5);
    TTS_ULP_EQUAL(eve::var(ev)                  , T(6.579736267392906)   , 0.5);
    TTS_ULP_EQUAL(eve::stdev(ev)                , T(2.565099660323728) , 0.5);
    TTS_ULP_EQUAL(eve::cdf(ev, T(0.0))          , T(4.547607881073950e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(ev, T(1.0))          , T(1.839397205857212e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ev, T(0.0))       , -inf   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ev, T(1.0))       , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ev, T(0.5))       , T(2.669741588366713e-01)   , 0.5);
  }
  {
    auto ev = eve::ev_distribution{eve::zero, T(2.0)};
    TTS_ULP_EQUAL(eve::median(ev)               , T(7.330258411633287e-01)  , 0.5);
    TTS_ULP_EQUAL(eve::mean(ev)                 , T(1.154431329803066)  , 0.5);
    TTS_ULP_EQUAL(eve::var(ev)                  , T(6.579736267392906)  , 0.5);
    TTS_ULP_EQUAL(eve::stdev(ev)                , T(2.565099660323728)  , 0.5);
    TTS_ULP_EQUAL(eve::cdf(ev, T(1.0))          , T(8.077043544520350e-01)   , 1);
    TTS_ULP_EQUAL(eve::pdf(ev, T(1.0))          , T(1.585209605389711e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(ev, T(0.0))       , -inf   , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ev, T(1.0))       , inf    , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ev, T(0.5))       , T(-7.330258411633287e-01)   , 0.5);
  }
  {
    auto ev = eve::ev_distribution_01<T>;
    TTS_ULP_EQUAL(eve::median(ev)               , T(3.665129205816643e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::mean(ev)                 , T(0.57721566490153286)     , 0.5);
    TTS_ULP_EQUAL(eve::var(ev)                  , T(1.644934066848226)       , 1.0);
    TTS_ULP_EQUAL(eve::stdev(ev)                , T(1.282549830161864)       , 0.5);
    TTS_ULP_EQUAL(eve::cdf(ev, T(1.0))          , T(9.340119641546875e-01)   , 0.5);
    TTS_ULP_EQUAL(eve::pdf(ev, T(1.0))          , T(1.793740787340172e-01)   , 1.0);
    TTS_ULP_EQUAL(eve::invcdf(ev, T(0.0))       , -inf                       , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ev, T(1.0))       , inf                        , 0.5);
    TTS_ULP_EQUAL(eve::invcdf(ev, T(0.5))       , T(-3.665129205816643e-01)  , 0.5);
  }
};
