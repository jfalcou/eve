//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nearest.hpp>

TTS_CASE_TPL("Check nearest return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::nearest(T()), T);
}

TTS_CASE_TPL("Check eve::nearest behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::nearest(T(0)), T(0));
  TTS_EQUAL(eve::nearest(T(1)), T(1));
  TTS_EQUAL(eve::nearest(T(2)), T(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::nearest(static_cast<T>(-1)), T(-1));
    TTS_EQUAL(eve::nearest(static_cast<T>(-2)), T(-2));
  }

  if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::nearest(static_cast<T>(-1.3)), T(-1));
   TTS_EQUAL(eve::nearest(static_cast<T>(-1.5)), T(-2));
   TTS_EQUAL(eve::nearest(static_cast<T>(-1.6)), T(-2));
   TTS_EQUAL(eve::nearest(static_cast<T>( 1.3)), T( 1));
   TTS_EQUAL(eve::nearest(static_cast<T>( 1.5)), T( 2));
   TTS_EQUAL(eve::nearest(static_cast<T>( 1.6)), T( 2));

   TTS_EQUAL(eve::nearest(static_cast<T>(-2.3)), T(-2));
   TTS_EQUAL(eve::nearest(static_cast<T>(-2.5)), T(-2));
   TTS_EQUAL(eve::nearest(static_cast<T>(-2.6)), T(-3));
   TTS_EQUAL(eve::nearest(static_cast<T>( 2.3)), T( 2));
   TTS_EQUAL(eve::nearest(static_cast<T>( 2.5)), T( 2));
   TTS_EQUAL(eve::nearest(static_cast<T>( 2.6)), T( 3));
  }
}
