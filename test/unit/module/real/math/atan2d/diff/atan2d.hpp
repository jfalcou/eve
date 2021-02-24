//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/atan2d.hpp>
#include <eve/function/radindeg.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(atan2) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::atan2d)(T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::atan2) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::atan2d)(T{3},T{4}), eve::radindeg(T(4.0/25.0)));
    TTS_EQUAL(eve::diff_2nd(eve::atan2d)(T{3},T{4}), eve::radindeg(T(3.0/25.0)));
  }
}
