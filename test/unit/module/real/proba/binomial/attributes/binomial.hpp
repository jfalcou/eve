//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/binomial.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/half.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::binomial behavior", EVE_TYPE)
{

  auto bino = eve::binomial{T(4), T(0.25)};
  TTS_ULP_EQUAL(eve::median(bino)               , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::mean(bino)                 , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::var(bino)                  , T(0.75)  , 0);
  TTS_ULP_EQUAL(eve::stdev(bino)                , T(8.660254037844386e-01)  , 0);
  TTS_ULP_EQUAL(eve::cdf(bino, T(0.0))          , T(3.1640625e-01)   , 1.0);
  TTS_ULP_EQUAL(eve::pmf(bino, T(1.0))          , T(1.0546875e-3)   , 1.0);
}

TTS_CASE_TPL("Check eve::binomial behavior", EVE_TYPE)
{

  auto bino = eve::binomial{eve::one, T(0.25)};
  TTS_ULP_EQUAL(eve::median(bino)               , T(0.0)  , 0);
  TTS_ULP_EQUAL(eve::mean(bino)                 , T(0.25)  , 0);
  TTS_ULP_EQUAL(eve::var(bino)                  , T(1.875e-01)  , 0);
  TTS_ULP_EQUAL(eve::stdev(bino)                , T(4.330127018922193e-01)  , 0);
  TTS_ULP_EQUAL(eve::cdf(bino, T(0.0))          , T(0.75)   , 1.0);
  TTS_ULP_EQUAL(eve::pmf(bino, T(1.0))          , T(0.25)   , 1.0);
}
TTS_CASE_TPL("Check eve::binomial behavior", EVE_TYPE)
{

  auto bino = eve::binomial{T(4), eve::half};
  TTS_ULP_EQUAL(eve::median(bino)               , T(2.0)  , 0);
  TTS_ULP_EQUAL(eve::mean(bino)                 , T(2.0)  , 0);
  TTS_ULP_EQUAL(eve::var(bino)                  , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::stdev(bino)                , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::cdf(bino, T(0.0))          , T(0.0625)   , 1.0);
  TTS_ULP_EQUAL(eve::pmf(bino, T(1.0))          , T(1.041666666666667e-02)   , 1.0);
}

TTS_CASE_TPL("Check eve::binomial behavior", EVE_TYPE)
{

  auto bino = eve::bernouilli<T>;

  TTS_ULP_EQUAL(eve::median(bino)               , T(0.0)  , 0);
  TTS_ULP_EQUAL(eve::mean(bino)                 , T(0.5)  , 0);
  TTS_ULP_EQUAL(eve::var(bino)                  , T(0.25)  , 0);
  TTS_ULP_EQUAL(eve::stdev(bino)                , T(0.5)  , 0);
  TTS_ULP_EQUAL(eve::cdf(bino, T(0.0))          , T(0.5)   , 1.0);
  TTS_ULP_EQUAL(eve::pmf(bino, T(1.0))          , T(0.5)   , 1.0);
}
