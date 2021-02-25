//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/powm1.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(powm1) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::powm1)(T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::powm1) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::powm1)(T{2},T{3}), T(12));
    TTS_EQUAL(eve::diff_2nd(eve::powm1)(T{2},T{3}), T(8*eve::log_2(eve::as<T>())));
 }
}
