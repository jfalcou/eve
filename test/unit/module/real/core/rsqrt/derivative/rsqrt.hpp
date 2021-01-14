//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/rsqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(rsqrt) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using ui_t = eve::detail::as_integer_t<T, unsigned>;
    TTS_EXPR_IS(eve::diff(eve::rsqrt)(T(), unsigned()), T);
    TTS_EXPR_IS(eve::diff(eve::rsqrt)(T(), ui_t()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::rsqrt) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::diff(eve::rsqrt)(T{9}, 0u), T(1.0/3), 0.5);
    TTS_ULP_EQUAL(eve::diff(eve::rsqrt)(T{9}, 1u), T(-1/54.0), 0.5);
    TTS_ULP_EQUAL(eve::diff(eve::rsqrt)(T{9}, 2u), T(1/(4.0*81)), 0.5);
  }
}
