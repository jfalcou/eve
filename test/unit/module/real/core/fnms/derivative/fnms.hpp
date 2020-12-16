//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//===========================pow=======================================================================
#include <eve/function/derivative/fnms.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(fnms) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::fnms)(T(), T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::fnms) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative_1st(eve::fnms)(T{2},T{3},T{4}), T(-3));
    TTS_EQUAL(eve::derivative_2nd(eve::fnms)(T{2},T{3},T{4}), T(-2));
    TTS_EQUAL(eve::derivative_3rd(eve::fnms)(T{2},T{3},T{4}), T(-1));
 }
}
