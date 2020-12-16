//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/hypot.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(hypot) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative_1st(eve::hypot)(T(), T()), T);
    TTS_EXPR_IS(eve::derivative_2nd(eve::hypot)(T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::hypot) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::derivative_1st(eve::hypot)(T{4},T{3}), T(4.0/5), 0.5);
    TTS_ULP_EQUAL(eve::derivative_2nd(eve::hypot)(T{4},T{3}), T(3.0/5), 0.5);
//     TTS_EQUAL(eve::derivative_1st(eve::hypot)(T{4},T{3}, 0u), T(5));
//     TTS_EQUAL(eve::derivative_1st(eve::hypot)(T{4},T{3}, 1u), T(4.0/5));
//     TTS_EQUAL(eve::derivative_1st(eve::hypot)(T{4},T{3}, 2u), T(0));
//     TTS_EQUAL(eve::derivative_2nd(eve::hypot)(T{-4},T{3}, 0u), T(-1));
//     TTS_EQUAL(eve::derivative_2nd(eve::hypot)(T{-4},T{3}, 1u), T(-4.0/5));
//     TTS_EQUAL(eve::derivative_2nd(eve::hypot)(T{-4},T{3}, 2u), T(0));
  }
}
