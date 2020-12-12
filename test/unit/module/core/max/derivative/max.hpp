//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/max.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(max) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::max)(T(), T()), T);
    TTS_EXPR_IS(eve::derivative(eve::max)(T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::max) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative_1st(eve::max)(T{2},T{3}), T(0));
    TTS_EQUAL(eve::derivative_2nd(eve::max)(T{2},T{3}), T(1));
    TTS_EQUAL(eve::derivative_1st(eve::max)(T{4},T{3}), T(1));
    TTS_EQUAL(eve::derivative_2nd(eve::max)(T{4},T{3}), T(0));
  }
}
