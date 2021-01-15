//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/cbrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(cbrt) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::cbrt)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::cbrt) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::diff(eve::cbrt)(T{1000}), T(0.00333333333333333333), 3);
    TTS_ULP_EQUAL(eve::diff(eve::cbrt)(T{-1000}), T(0.00333333333333333333), 3);
  }
}
