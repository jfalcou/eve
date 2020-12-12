//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/pow_abs.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(pow_abs) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::pow_abs)(T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::pow_abs) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative_1st(eve::pow_abs)(T{2},T{3}), T(12));
    TTS_EQUAL(eve::derivative_2nd(eve::pow_abs)(T{2},T{3}), T(8*eve::log_2(eve::as<T>())));
 }
}
