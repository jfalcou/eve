//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/fnms.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(fnms) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::fnms)(T(), T(), T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::fnms) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::fnms)(T{2},T{3},T{4}), T(-3));
    TTS_EQUAL(eve::diff_2nd(eve::fnms)(T{2},T{3},T{4}), T(-2));
    TTS_EQUAL(eve::diff_3rd(eve::fnms)(T{2},T{3},T{4}), T(-1));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
