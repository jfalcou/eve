//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/average.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(average) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::average)(T(), T()), T);
    TTS_EXPR_IS(eve::diff(eve::average)(T(), T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::average) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::average)(T{10},T{6}), T(0.5));
    TTS_EQUAL(eve::diff_2nd(eve::average)(T{-10},T{6}), T(0.5));
    TTS_EQUAL(eve::diff_3rd(eve::average)(T{-10},T{6}), T(0.0));

    TTS_EQUAL(eve::diff_1st(eve::average)(T{10},T{6},T{4}), T(1.0/3));
    TTS_EQUAL(eve::diff_2nd(eve::average)(T{-10},T{6},T{4}), T(1.0/3));
    TTS_EQUAL(eve::diff_3rd(eve::average)(T{-10},T{6},T{4}), T(1.0/3));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
