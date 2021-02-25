//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/sqr.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(sqr) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using ui_t = eve::as_integer_t<T, unsigned>;
    TTS_EXPR_IS(eve::diff(eve::sqr)(T(), unsigned()), T);
    TTS_EXPR_IS(eve::diff(eve::sqr)(T(), ui_t()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::sqr) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff(eve::sqr)(T{10}, 0u), T(100));
    TTS_EQUAL(eve::diff(eve::sqr)(T{10}, 1u), T(20));
    TTS_EQUAL(eve::diff(eve::sqr)(T{10}, 2u), T(2));
    TTS_EQUAL(eve::diff(eve::sqr)(T{-10}, 0u), T(100));
    TTS_EQUAL(eve::diff(eve::sqr)(T{-10}, 1u), T(-20));
    TTS_EQUAL(eve::diff(eve::sqr)(T{-10}, 2u), T(2));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
