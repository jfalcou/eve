//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/atan2pi.hpp>
#include <eve/function/radinpi.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(atan2) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::atan2pi)(T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::atan2) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::atan2pi)(T{3},T{4}), eve::radinpi(T(4.0/25.0)));
    TTS_EQUAL(eve::diff_2nd(eve::atan2pi)(T{3},T{4}), eve::radinpi(T(3.0/25.0)));
  }
}
