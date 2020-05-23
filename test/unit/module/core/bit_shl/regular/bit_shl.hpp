//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_shl.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::bit_shl return type", EVE_TYPE)
{
  using ui_t = eve::detail::as_integer_t<T, unsigned>;
  using si_t = eve::detail::as_integer_t<T, signed>;

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
