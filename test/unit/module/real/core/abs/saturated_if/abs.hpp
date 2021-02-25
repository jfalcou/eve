//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/abs.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturated(eve::abs) conditional return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated(eve::abs[T()])(T()), T);
}

TTS_CASE_TPL("Check eve::saturated(eve::abs)  conditional behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturated(eve::abs[1])(T(0)), T(0));
  TTS_EQUAL(eve::saturated(eve::abs[1])(T(1)), T(1));
  TTS_EQUAL(eve::saturated(eve::abs[1])(T(2)), T(2));
  TTS_EQUAL(eve::saturated(eve::abs[0])(T(0)), T(0));
  TTS_EQUAL(eve::saturated(eve::abs[0])(T(1)), T(1));
  TTS_EQUAL(eve::saturated(eve::abs[0])(T(2)), T(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::abs[1])(T(-1)), T(1));
    TTS_EQUAL(eve::saturated(eve::abs[1])(T(-2)), T(2));
    TTS_EQUAL(eve::saturated(eve::abs[0])(T(-1)), T(-1));
    TTS_EQUAL(eve::saturated(eve::abs[0])(T(-2)), T(-2));
  }
}
