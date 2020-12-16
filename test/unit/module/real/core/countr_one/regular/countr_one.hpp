//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/countr_one.hpp>

TTS_CASE_TPL("Check countr_one return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::countr_one(T()), T);
}

TTS_CASE_TPL("Check eve::countr_one behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::countr_one(T(0))   , T(0));
  TTS_EQUAL(eve::countr_one(T(3))   , T(2));
  TTS_EQUAL(eve::countr_one(T(8))   , T(0));
  TTS_EQUAL(eve::countr_one(T(127)) , T(7));
  TTS_EQUAL(eve::countr_one(T(9))   , T(1));
}
