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

TTS_CASE("Check bit_width return type")
{
  TTS_EXPR_IS(eve::bit_width(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::bit_width behavior")
{
  TTS_EQUAL(eve::bit_width(EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::bit_width(EVE_TYPE(3)), EVE_TYPE(2));
  TTS_EQUAL(eve::bit_width(EVE_TYPE(8)), EVE_TYPE(4));
  TTS_EQUAL(eve::bit_width(EVE_TYPE(6)), EVE_TYPE(3));
  TTS_EQUAL(eve::bit_width(EVE_TYPE(9)), EVE_TYPE(4));
}
