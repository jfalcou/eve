//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/trunc.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::trunc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::trunc(T()), T);
}

TTS_CASE_TPL("Check eve::trunc behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::trunc(T(0)), T(0) );
  TTS_EQUAL(eve::trunc(T(1)), T(1) );
  TTS_EQUAL(eve::trunc(T(2)), T(2) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::trunc(static_cast<T>(-1)), T(-1) );
    TTS_EQUAL(eve::trunc(static_cast<T>(-2)), T(-2) );
  }

  if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::trunc(static_cast<T>(-1.3)), T(-1) );
   TTS_EQUAL(eve::trunc(static_cast<T>(-1.5)), T(-1) );
   TTS_EQUAL(eve::trunc(static_cast<T>(-1.6)), T(-1) );
   TTS_EQUAL(eve::trunc(static_cast<T>( 1.3)), T( 1) );
   TTS_EQUAL(eve::trunc(static_cast<T>( 1.5)), T( 1) );
   TTS_EQUAL(eve::trunc(static_cast<T>( 1.6)), T( 1) );
  }
}
