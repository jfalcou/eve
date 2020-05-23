//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_width.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check bit_width return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::bit_width(T()), T);
}

TTS_CASE_TPL("Check eve::bit_width behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::bit_width(T(0)), T(0));
  TTS_EQUAL(eve::bit_width(T(3)), T(2));
  TTS_EQUAL(eve::bit_width(T(8)), T(4));
  TTS_EQUAL(eve::bit_width(T(6)), T(3));
  TTS_EQUAL(eve::bit_width(T(9)), T(4));
}
