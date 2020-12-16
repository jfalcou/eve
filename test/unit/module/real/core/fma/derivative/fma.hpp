//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//===========================pow=======================================================================
#include <eve/function/derivative/fma.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(fma) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::fma)(T(), T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::fma) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative_1st(eve::fma)(T{2},T{3},T{4}), T(3));
    TTS_EQUAL(eve::derivative_2nd(eve::fma)(T{2},T{3},T{4}), T(2));
    TTS_EQUAL(eve::derivative_3rd(eve::fma)(T{2},T{3},T{4}), T(1));
 }
}
