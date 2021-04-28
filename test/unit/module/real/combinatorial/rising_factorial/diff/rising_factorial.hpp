//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/rising_factorial.hpp>
#include <eve/constant/eps.hpp>

#include <type_traits>


TTS_CASE_TPL("Check eve::rising_factorial return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::diff_1st)(eve::rising_factorial)(int(), T()), T);
  TTS_EXPR_IS(eve::pedantic(eve::diff_2nd)(eve::rising_factorial)( T (), T()), T);
  TTS_EXPR_IS(eve::diff_1st(eve::rising_factorial)(int(), T()), T);
  TTS_EXPR_IS(eve::diff_2nd(eve::rising_factorial)( T (), T()), T);

}

TTS_CASE_TPL("Check eve::rising_factorial behavior", EVE_TYPE)
{

  auto ulp = 70.0;
  TTS_ULP_EQUAL(eve::diff_2nd(eve::rising_factorial)(T( 20),   T(2.0))   , T(1.288620076741702e+03), ulp);
  TTS_ULP_EQUAL(eve::diff_1st(eve::rising_factorial)(T( 20),   T(2.0))   , T(4.100000000000004e+01), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_2nd)(eve::rising_factorial)(T( 20),   T(2.0))   , T(1.288620076741702e+03), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_1st)(eve::rising_factorial)(T( 20),   T(2.0))   , T(4.100000000000004e+01), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_1st)(eve::rising_factorial)(T(-20.2),   T(2.0))   , T(-39.399999999999522515), ulp);
  TTS_ULP_EQUAL(eve::diff_1st(eve::rising_factorial)(T(-20.2),   T(2.0))   , eve::nan(eve::as<T>()), ulp);
}
