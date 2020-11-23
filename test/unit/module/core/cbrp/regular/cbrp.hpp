//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cbrp.hpp>
#include <eve/function/average.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/eps.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::cbrp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cbrp(T(), T(), T(), T(), T()), T);
}

TTS_CASE_TPL("Check eve::(eve::cbrp) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL ( eve::cbrp(T(12.73), T(0), T(27.6666), T(0), T(1)), T(27.6666), 0);
  TTS_ULP_EQUAL ( eve::cbrp(T(12.73), T(0), T(27.6666), T(0), T(0)), T(12.73), 0);
  TTS_ULP_EQUAL ( eve::cbrp(T(1), T(0.2), T(1), T(-0.2), T(0.5)), T(1.050), 0);
}
