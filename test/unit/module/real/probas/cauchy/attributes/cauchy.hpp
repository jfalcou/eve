//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cauchy.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::cauchy behavior", EVE_TYPE)
{
  auto inf  = eve::inf(eve::as<T>());

  auto ca = eve::cauchy{T(1.0), T(2.0)};
  TTS_ULP_EQUAL(eve::median(ca)          , T(1.0)  , 0);
  TTS_ULP_EQUAL(eve::scale(ca)           , T(2.0)  , 0);
  TTS_ULP_EQUAL(eve::cdf(ca, T(0.0))     , T(3.524163823495667e-01)   , 0.5);
  TTS_ULP_EQUAL(eve::pdf(ca, T(1.0))     , T(1.591549430918953e-01)   , 1.0);
  TTS_ULP_EQUAL(eve::invcdf(ca, T(0.0))  , -inf   , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ca, T(1.0))  , inf    , 0.5);
  TTS_ULP_EQUAL(eve::invcdf(ca, T(0.5))  , T(1)    , 0.5);
}
