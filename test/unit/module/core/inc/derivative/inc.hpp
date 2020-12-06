//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/inc.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(inc) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using ui_t = eve::detail::as_integer_t<T, unsigned>;
    TTS_EXPR_IS(eve::derivative(eve::inc)(T(), unsigned()), T);
    TTS_EXPR_IS(eve::derivative(eve::inc)(T(), ui_t()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::inc) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative(eve::inc)(T{10}, 0u), T(11));
    TTS_EQUAL(eve::derivative(eve::inc)(T{10}, 1u), T(1));
    TTS_EQUAL(eve::derivative(eve::inc)(T{10}, 2u), T(0));
    TTS_EQUAL(eve::derivative(eve::inc)(T{-10}, 0u), T(-9));
    TTS_EQUAL(eve::derivative(eve::inc)(T{-10}, 1u), T(1));
    TTS_EQUAL(eve::derivative(eve::inc)(T{-10}, 2u), T(0));
  }
}
