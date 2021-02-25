//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/div.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(div) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::div)(T(), T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::div) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::diff_1st(eve::div)(T{10},T{5}), T(0.2), 0.5);
    TTS_ULP_EQUAL(eve::diff_2nd(eve::div)(T{10},T{5}), T(-10/25.0), 0.5);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
