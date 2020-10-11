//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/conj.hpp>

TTS_CASE_TPL("Check eve::conj return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::conj(T(0)), T);
}

TTS_CASE_TPL("Check eve::conj behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::conj(T(1)), T(1), 0.5);
}
