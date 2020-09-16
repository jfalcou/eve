//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sub.hpp>

#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::sub return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sub(T(), T()), T);
}

TTS_CASE_TPL("Check eve::sub behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::sub(T(0), T(0)), T(0));
  TTS_EQUAL(eve::sub(T(1), T(1)), T(0));
  TTS_EQUAL(eve::sub(T(6), T(2)), T(4));

  TTS_EQUAL(eve::sub(v_t(0), T(0)), T(0));
  TTS_EQUAL(eve::sub(v_t(1), T(1)), T(0));
  TTS_EQUAL(eve::sub(v_t(6), T(2)), T(4));

  TTS_EQUAL(eve::sub(T(0), v_t(0)), T(0));
  TTS_EQUAL(eve::sub(T(1), v_t(1)), T(0));
  TTS_EQUAL(eve::sub(T(6), v_t(2)), T(4));

  if constexpr(std::is_signed_v<v_t>)
  {
    TTS_EQUAL(eve::sub(  T(-1),   T( 1)), T(-2));
    TTS_EQUAL(eve::sub(  T(-2),   T(-6)), T( 4));
    TTS_EQUAL(eve::sub(v_t(-1),   T( 1)), T(-2));
    TTS_EQUAL(eve::sub(v_t(-2),   T(-6)), T( 4));
    TTS_EQUAL(eve::sub(  T(-1), v_t( 1)), T(-2));
    TTS_EQUAL(eve::sub(  T(-2), v_t(-6)), T( 4));
  }
}
