//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_width.hpp>

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
