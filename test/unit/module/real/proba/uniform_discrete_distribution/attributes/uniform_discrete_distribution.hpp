//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/uniform_discrete_distribution.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::uniform_discrete_distribution behavior", EVE_TYPE)
{

  auto d = eve::uniform_discrete_distribution{T(1), T(2)};
  TTS_ULP_EQUAL(eve::median(d)               , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::mean(d)                 , T(1.5)  , 0);
  TTS_ULP_EQUAL(eve::var(d)                  , T(0.25)  , 0);
  TTS_ULP_EQUAL(eve::stdev(d)                , T(0.5)  , 1);
  TTS_ULP_EQUAL(eve::cdf(d, T(0.0))          , T(0)   , 1.0);
  TTS_ULP_EQUAL(eve::cdf(d, T(1.5))          , T(0.5) , 1.0);
  TTS_ULP_EQUAL(eve::pmf(d, T(1.0))          , T(0.5)   , 1.0);
}

TTS_CASE_TPL("Check eve::uniform_discrete_distribution behavior", EVE_TYPE)
{

  auto d = eve::uniform_discrete_distribution_01<T>;

  TTS_ULP_EQUAL(eve::median(d)               , T(0)  , 0);
  TTS_ULP_EQUAL(eve::mean(d)                 , T(0.5)  , 0);
  TTS_ULP_EQUAL(eve::var(d)                  , T(0.25)  , 0);
  TTS_ULP_EQUAL(eve::stdev(d)                , T(0.5)  , 1);
  TTS_ULP_EQUAL(eve::cdf(d, T(0.0))          , T(0.5)   , 1.0);
  TTS_ULP_EQUAL(eve::pmf(d, T(1.0))          , T(0.5)   , 1.0);
}
