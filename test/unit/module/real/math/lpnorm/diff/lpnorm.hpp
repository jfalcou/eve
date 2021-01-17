//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/lpnorm.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(lpnorm) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff_1st(eve::lpnorm)(T(), T(), T()), T);
    TTS_EXPR_IS(eve::diff_2nd(eve::lpnorm)(T(), T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::lpnorm) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::diff_1st(eve::lpnorm)(2, T{4},T{3}), T(4.0/5), 0.5);
    TTS_ULP_EQUAL(eve::diff_2nd(eve::lpnorm)(2, T{4},T{3}), T(3.0/5), 0.5);
    TTS_ULP_EQUAL(eve::diff_3rd(eve::lpnorm)(2, T{2},T{2},T{4}), T(4.0/eve::sqrt(24.0)), 0.5);
    TTS_ULP_EQUAL(eve::diff_nth<4>(eve::lpnorm)(2, T{1},T{2},T{3},T{4}), T(4.0/eve::sqrt(30.0)), 0.5);
    TTS_ULP_EQUAL(eve::pedantic(eve::diff_1st)(eve::lpnorm)(2, T{4},T{3}), T(4.0/5), 0.5);
    TTS_ULP_EQUAL(eve::pedantic(eve::diff_2nd)(eve::lpnorm)(2, T{4},T{3}), T(3.0/5), 0.5);
    TTS_ULP_EQUAL(eve::pedantic(eve::diff_3rd)(eve::lpnorm)(2, T{2},T{2},T{4}), T(4.0/eve::sqrt(24.0)), 0.5);
    TTS_ULP_EQUAL(eve::pedantic(eve::diff_nth<4>)(eve::lpnorm)(2, T{1},T{2},T{3},T{4}), T(4.0/eve::sqrt(30.0)), 0.5);

  }
}
