//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/popcount.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::popcount return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::popcount(T(0)), (eve::detail::as_integer_t<T, unsigned>) );
}

TTS_CASE_TPL("Check eve::popcount behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using r_t = eve::detail::as_integer_t<T, unsigned>;

  TTS_EQUAL(eve::popcount( T(0) ) , r_t(0));
  TTS_EQUAL(eve::popcount( T(1) ) , r_t(1));
  TTS_EQUAL(eve::popcount( T(2) ) , r_t(1));
  TTS_EQUAL(eve::popcount( T(3) ) , r_t(2));
  TTS_EQUAL(eve::popcount( T(11)) , r_t(3));

  TTS_EQUAL(eve::popcount( eve::Valmax<T>()), r_t(sizeof(v_t)*8-eve::signed_value<T>));
  TTS_EQUAL(eve::popcount( T(~0)),            r_t(sizeof(v_t)*8));
}
