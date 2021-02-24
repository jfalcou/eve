//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/lrising_factorial.hpp>
#include <eve/function/diff/lrising_factorial.hpp>
#include <eve/constant/eps.hpp>

#include <type_traits>


TTS_CASE_TPL("Check eve::rising_factorial return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::diff_1st)(eve::lrising_factorial)(int(), T()), T);
  TTS_EXPR_IS(eve::pedantic(eve::diff_2nd)(eve::lrising_factorial)( T (), T()), T);
  TTS_EXPR_IS(eve::diff_1st(eve::lrising_factorial)(int(), T()), T);
  TTS_EXPR_IS(eve::diff_2nd(eve::lrising_factorial)( T (), T()), T);

}

TTS_CASE_TPL("Check eve::lrising_factorial behavior", EVE_TYPE)
{

  auto ulp = 110.0;
  TTS_ULP_EQUAL(eve::diff_2nd(eve::lrising_factorial)(T( 20),   T(2.0))   , T(3.068143039861197e+00), ulp);
  TTS_ULP_EQUAL(eve::diff_1st(eve::lrising_factorial)(T( 20),   T(2.0))   , T(9.761904761904772e-02), ulp);
  TTS_ULP_EQUAL((eve::pedantic(eve::diff_2nd))(eve::lrising_factorial)(T( 20),   T(2.0))   , T(3.068143039861197e+00), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_1st)(eve::lrising_factorial)(T( 20),   T(2.0))   , T(9.761904761904772e-02), ulp);

  TTS_ULP_EQUAL(eve::diff_1st(eve::lrising_factorial)(10, T(0.1))         , T(1.046176802742682e-02), ulp);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::lrising_factorial)(10, T(0.1))         , T(2.262214357094148e+00), ulp);;
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_1st)(eve::lrising_factorial)(10, T(0.1))         , T(1.046176802742682e-02), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_2nd)(eve::lrising_factorial)(10, T(0.1))         , T(2.262214357094148e+00), ulp);;
}
