//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/pow.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(pow) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::pow)(T(), T()), T);
    TTS_EXPR_IS(eve::diff(eve::pow)(T(), T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::pow) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::pow)(T{2},T{3}), T(12));
    TTS_EQUAL(eve::diff_2nd(eve::pow)(T{2},T{3}), T(8*eve::log_2(eve::as<T>())));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
