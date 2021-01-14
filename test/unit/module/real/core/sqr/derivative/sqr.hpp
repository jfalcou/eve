//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/sqr.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(sqr) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using ui_t = eve::detail::as_integer_t<T, unsigned>;
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
