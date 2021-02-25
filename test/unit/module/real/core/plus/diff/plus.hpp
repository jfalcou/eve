//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/plus.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(plus) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using ui_t = eve::as_integer_t<T, unsigned>;
    TTS_EXPR_IS(eve::diff(eve::plus)(T(), unsigned()), T);
    TTS_EXPR_IS(eve::diff(eve::plus)(T(), ui_t()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::plus) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff(eve::plus)(T{10}, 0u), T(10));
    TTS_EQUAL(eve::diff(eve::plus)(T{10}, 1u), T(1));
    TTS_EQUAL(eve::diff(eve::plus)(T{10}, 2u), T(0));
    TTS_EQUAL(eve::diff(eve::plus)(T{-10}, 0u), T(-10));
    TTS_EQUAL(eve::diff(eve::plus)(T{-10}, 1u), T(1));
    TTS_EQUAL(eve::diff(eve::plus)(T{-10}, 2u), T(0));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
