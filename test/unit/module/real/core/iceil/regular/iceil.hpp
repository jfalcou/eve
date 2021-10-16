//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/ceil.hpp>

TTS_CASE_TPL("Check iceil return type", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  TTS_EXPR_IS(eve::int_(eve::ceil)(T()), eve::as_integer_t<T>);
};

TTS_CASE_TPL("Check eve::iceil behavior", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using i_t = eve::as_integer_t<T>;

  TTS_EQUAL(eve::int_(eve::ceil)(T(0)), i_t(0));
  TTS_EQUAL(eve::int_(eve::ceil)(T(1)), i_t(1));
  TTS_EQUAL(eve::int_(eve::ceil)(T(2)), i_t(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::int_(eve::ceil)(T(-1)), i_t(-1));
    TTS_EQUAL(eve::int_(eve::ceil)(T(-2)), i_t(-2));
  }

  if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::int_(eve::ceil)(T(-1.3)), i_t(-1));
   TTS_EQUAL(eve::int_(eve::ceil)(T(-1.5)), i_t(-1));
   TTS_EQUAL(eve::int_(eve::ceil)(T(-1.6)), i_t(-1));
   TTS_EQUAL(eve::int_(eve::ceil)(T( 1.3)) , i_t( 2));
   TTS_EQUAL(eve::int_(eve::ceil)(T( 1.5)) , i_t( 2));
   TTS_EQUAL(eve::int_(eve::ceil)(T( 1.6)) , i_t( 2));
  }
};
