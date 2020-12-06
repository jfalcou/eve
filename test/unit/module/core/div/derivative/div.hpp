//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/div.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(div) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using ui_t = eve::detail::as_integer_t<T, unsigned>;
    TTS_EXPR_IS(eve::derivative(eve::div)(T(), T(), unsigned(), unsigned()), T);
    TTS_EXPR_IS(eve::derivative(eve::div)(T(), T(), ui_t(), ui_t()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::div) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::derivative(eve::div)(T{10},T{5}, 0u, 0u), T(2), 0.5);
    TTS_ULP_EQUAL(eve::derivative(eve::div)(T{10},T{5}, 1u, 0u), T(0.2), 0.5);
    TTS_ULP_EQUAL(eve::derivative(eve::div)(T{10},T{5}, 2u, 0u), T(0), 0.5);
    TTS_ULP_EQUAL(eve::derivative(eve::div)(T{10},T{5}, 0u, 1u), T(-10/25.0), 0.5);
    TTS_ULP_EQUAL(eve::derivative(eve::div)(T{10},T{5}, 1u, 1u), T(-1/25.0), 0.5);
    TTS_ULP_EQUAL(eve::derivative(eve::div)(T{10},T{5}, 0u, 2u), T(20/125.0), 0.5);
  }
}
