//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_shl.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::bit_shl return type")
{
  using ui_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Type, signed>;

  TTS_EXPR_IS(eve::bit_shl(Type(), int()) , (Type));
  TTS_EXPR_IS(eve::bit_shl(Type(), ui_t()), (Type));
  TTS_EXPR_IS(eve::bit_shl(Type(), si_t()), (Type));
}

TTS_CASE( "Check eve::bit_shl behavior")
{
  TTS_EQUAL(eve::bit_shl((Type(7)), (Type(4))), (Type(112)));
  TTS_EQUAL(eve::bit_shl((Type(1)), (Type(1))), (Type(  2)));
  TTS_EQUAL(eve::bit_shl((Type(1)), (Type(0))), (Type(  1)));
  TTS_EQUAL(eve::bit_shl((Type(0)), (Type(1))), (Type(  0)));
}
