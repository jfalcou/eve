//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/countl_zero.hpp>

#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check countl_zero return type") { TTS_EXPR_IS(eve::countl_zero(EVE_TYPE()), (EVE_TYPE)); }

TTS_CASE("Check eve::countl_zero behavior")
{
  TTS_EQUAL(eve::countl_zero(EVE_TYPE(0)), EVE_TYPE(sizeof(EVE_VALUE) * 8));
  TTS_EQUAL(eve::countl_zero(EVE_TYPE(3)), EVE_TYPE(sizeof(EVE_VALUE) * 8 - 2));
  TTS_EQUAL(eve::countl_zero(EVE_TYPE(5)), EVE_TYPE(sizeof(EVE_VALUE) * 8 - 3));
  TTS_EQUAL(eve::countl_zero(EVE_TYPE(6)), EVE_TYPE(sizeof(EVE_VALUE) * 8 - 3));
  TTS_EQUAL(eve::countl_zero(EVE_TYPE(9)), EVE_TYPE(sizeof(EVE_VALUE) * 8 - 4));
}
