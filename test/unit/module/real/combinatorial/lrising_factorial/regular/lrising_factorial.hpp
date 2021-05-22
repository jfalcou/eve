//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lrising_factorial.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::lrising_factorial return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw(eve::lrising_factorial)(int(), T()), T);
}

TTS_CASE_TPL("Check eve::lrising_factorial behavior", EVE_TYPE)
{
  auto ulp = sizeof(eve::element_type_t<T>) == 4 ? 70 : 20;
  TTS_ULP_EQUAL(eve::lrising_factorial(T( 20),   T(2.0))   , T(6.040254711277414e+00), ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(10, T(0.1))         , T(2.256992585517679e-01), ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(5,  T(0.1))         , T(1.517103381272788e-01) , ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(0,  T(0.1))         , eve::nan(eve::as<T>()) , ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(2,  T(0.1))         , T(4.543773854448513e-02) , ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(T(20.3), T(10.2))   , T(3.272013434873217e+01), ulp);
}
