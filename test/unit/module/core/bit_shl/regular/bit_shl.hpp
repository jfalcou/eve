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
  using ui_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;
  using si_t = eve::detail::as_integer_t<EVE_TYPE, signed>;

  TTS_EXPR_IS(eve::bit_shl(EVE_TYPE(), int()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_shl(EVE_TYPE(), ui_t()), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_shl(EVE_TYPE(), si_t()), (EVE_TYPE));
}

TTS_CASE( "Check eve::bit_shl behavior")
{
  TTS_EQUAL(eve::bit_shl((EVE_TYPE(7)), (EVE_TYPE(4))), (EVE_TYPE(112)));
  TTS_EQUAL(eve::bit_shl((EVE_TYPE(1)), (EVE_TYPE(1))), (EVE_TYPE(  2)));
  TTS_EQUAL(eve::bit_shl((EVE_TYPE(1)), (EVE_TYPE(0))), (EVE_TYPE(  1)));
  TTS_EQUAL(eve::bit_shl((EVE_TYPE(0)), (EVE_TYPE(1))), (EVE_TYPE(  0)));
}
