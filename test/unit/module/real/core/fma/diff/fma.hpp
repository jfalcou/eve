//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/fma.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(fma) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::fma)(T(), T(), T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::fma) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::fma)(T{2},T{3},T{4}), T(3));
    TTS_EQUAL(eve::diff_2nd(eve::fma)(T{2},T{3},T{4}), T(2));
    TTS_EQUAL(eve::diff_3rd(eve::fma)(T{2},T{3},T{4}), T(1));
 }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
