//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_shl.hpp>

TTS_CASE_TPL("Check eve::bit_shl return type", EVE_TYPE)
{
  using ui_t = eve::as_integer_t<T, unsigned>;
  using si_t = eve::as_integer_t<T, signed>;

  TTS_EXPR_IS(eve::bit_shl(T(), int()) , T);
  TTS_EXPR_IS(eve::bit_shl(T(), ui_t()), T);
  TTS_EXPR_IS(eve::bit_shl(T(), si_t()), T);
}

TTS_CASE_TPL( "Check eve::bit_shl behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::bit_shl(T(7), T(4)), T(112) );
  TTS_EQUAL(eve::bit_shl(T(1), T(1)), T(  2) );
  TTS_EQUAL(eve::bit_shl(T(1), T(0)), T(  1) );
  TTS_EQUAL(eve::bit_shl(T(0), T(1)), T(  0) );
}
