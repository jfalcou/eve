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
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::binomial behavior", EVE_TYPE)
{

  auto bino = eve::binomial{T(4), T(0.25)};
  TTS_ULP_EQUAL(eve::median(bino)               , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::mean(bino)                 , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::var(bino)                  , T(0.562500)  , 0);
  TTS_ULP_EQUAL(eve::stdev(bino)                , T(0.750000)  , 0);
  TTS_ULP_EQUAL(eve::cdf(bino, T(0.0))          , T(3.1640625e-01)   , 1.0);
  TTS_ULP_EQUAL(eve::pmf(bino, T(1.0))          , T(1.0546875e-3)   , 1.0);
}
