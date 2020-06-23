//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nearest.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check inearest return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::int_(eve::nearest)(T()), eve::detail::as_integer_t<T>);
}

TTS_CASE_TPL("Check eve::int_(eve::nearest) behavior", EVE_TYPE)
{
  using i_t = eve::detail::as_integer_t<T>;

  TTS_EQUAL(eve::int_(eve::nearest)(T(0)), i_t(0));
  TTS_EQUAL(eve::int_(eve::nearest)(T(1)), i_t(1));
  TTS_EQUAL(eve::int_(eve::nearest)(T(2)), i_t(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::int_(eve::nearest)(T(-1)), i_t(-1));
    TTS_EQUAL(eve::int_(eve::nearest)(T(-2)), i_t(-2));
  }

  if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::int_(eve::nearest)(T(-1.3)), i_t(-1));
   TTS_EQUAL(eve::int_(eve::nearest)(T(-1.5)), i_t(-2));
   TTS_EQUAL(eve::int_(eve::nearest)(T(-1.6)), i_t(-2));
   TTS_EQUAL(eve::int_(eve::nearest)(T( 1.3)) , i_t( 1));
   TTS_EQUAL(eve::int_(eve::nearest)(T( 1.5)) , i_t( 2));
   TTS_EQUAL(eve::int_(eve::nearest)(T( 1.6)) , i_t( 2));
   TTS_EQUAL(eve::int_(eve::nearest)(T(-2.3)), i_t(-2));
   TTS_EQUAL(eve::int_(eve::nearest)(T(-2.5)), i_t(-2));
   TTS_EQUAL(eve::int_(eve::nearest)(T(-2.6)), i_t(-3));
   TTS_EQUAL(eve::int_(eve::nearest)(T( 2.3)) , i_t( 2));
   TTS_EQUAL(eve::int_(eve::nearest)(T( 2.5)) , i_t( 2));
   TTS_EQUAL(eve::int_(eve::nearest)(T( 2.6)) , i_t( 3));
  }
}
