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
    TTS_EXPR_IS(eve::derivative(eve::div)(T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::div) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::derivative_1st(eve::div)(T{10},T{5}), T(0.2), 0.5);
    TTS_ULP_EQUAL(eve::derivative_2nd(eve::div)(T{10},T{5}), T(-10/25.0), 0.5);
  }
}
