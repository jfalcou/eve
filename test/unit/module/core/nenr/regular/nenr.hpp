//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nenr.hpp>
#include <eve/function/average.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/eps.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::nenr return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::nenr(T(), T(), T()), T);
}

TTS_CASE_TPL("Check eve::(eve::nenr) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::nenr(T(12.73), T(27.6666), T(1)), T(27.6666)                           , 0 );
  TTS_ULP_EQUAL(eve::nenr(T(12.73), T(27.6666), T(0)), T(12.73)                             , 0 );
  TTS_ULP_EQUAL(eve::nenr(T(12.73), T(27.6666), T(0.4)), T(12.73)                           , 0 );
  TTS_ULP_EQUAL(eve::nenr(T(12.73), T(27.6666), T(0.5)), T(12.73)                           , 0 );
  TTS_ULP_EQUAL(eve::nenr(T(12.73), T(27.6666), T(0.6)), T(27.6666)                         , 0 );
}
