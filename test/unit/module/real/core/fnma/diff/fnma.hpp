//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//===========================pow=======================================================================
#include <eve/function/diff/fnma.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(fnma) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::fnma)(T(), T(), T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::fnma) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::fnma)(T{2},T{3},T{4}), T(-3));
    TTS_EQUAL(eve::diff_2nd(eve::fnma)(T{2},T{3},T{4}), T(-2));
    TTS_EQUAL(eve::diff_3rd(eve::fnma)(T{2},T{3},T{4}), T(1));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
