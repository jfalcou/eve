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

TTS_CASE("Check countr_one return type")
{
  TTS_EXPR_IS(eve::countr_one(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::countr_one behavior")
{
  TTS_EQUAL(eve::countr_one(EVE_TYPE(0))   , EVE_TYPE(0));
  TTS_EQUAL(eve::countr_one(EVE_TYPE(3))   , EVE_TYPE(2));
  TTS_EQUAL(eve::countr_one(EVE_TYPE(8))   , EVE_TYPE(0));
  TTS_EQUAL(eve::countr_one(EVE_TYPE(127)) , EVE_TYPE(7));
  TTS_EQUAL(eve::countr_one(EVE_TYPE(9))   , EVE_TYPE(1));
}
