//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rising_factorial.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::rising_factorial return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw(eve::rising_factorial)(int(), T()), T);
}

TTS_CASE_TPL("Check eve::rising_factorial behavior", EVE_TYPE)
{
  auto ulp = sizeof(eve::element_type_t<T>) == 4 ? 70 : 40;
  TTS_ULP_EQUAL(eve::raw(eve::rising_factorial)(T( 20),   T(2.0))   , T(420), ulp);
  TTS_ULP_EQUAL(eve::raw(eve::rising_factorial)(10, T(0.1))         , T(1.253198719801548e+00), ulp);
  TTS_ULP_EQUAL(eve::raw(eve::rising_factorial)(5,  T(0.1))         , T(1.163823072432015e+00) , ulp);
  TTS_ULP_EQUAL(eve::raw(eve::rising_factorial)(2,  T(0.1))         , T(1.046485846853560e+00) , ulp);
  TTS_ULP_EQUAL(eve::raw(eve::rising_factorial)(T(20.3), T(10.2))   , T(1.622459238800527e+14), ulp);
}
