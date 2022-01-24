//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/special.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::rising_factorial"
              , eve::test::simd::ieee_reals)
<typename T>(eve::as<T>)
{
  TTS_EXPR_IS(eve::raw(eve::rising_factorial)(int(), T()), T);

};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST_TYPES( "Check corner-cases behavior of eve::rising_factorial wide"
        , eve::test::simd::ieee_reals
         )
  <typename T>(eve::as<T>)
{
  using eve::as;
  auto ulp = sizeof(eve::element_type_t<T>) == 4 ? 70 : 40;
  TTS_ULP_EQUAL(eve::rising_factorial(T( 20),   T(2.0))   , T(420), ulp);
  TTS_ULP_EQUAL(eve::rising_factorial(10, T(0.1))         , T(1.253198719801548e+00), ulp);
  TTS_ULP_EQUAL(eve::rising_factorial(5,  T(0.1))         , T(1.163823072432015e+00) , ulp);
  TTS_ULP_EQUAL(eve::rising_factorial(2,  T(0.1))         , T(1.046485846853560e+00) , ulp);
  TTS_ULP_EQUAL(eve::rising_factorial(T(20.3), T(10.2))   , T(1.622459238800527e+14), ulp);
  TTS_ULP_EQUAL(eve::rising_factorial(T(5), 10*eve::eps(eve::as<T>())), T(1.000000000000003e+00), ulp);

    if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(eve::nan(eve::as<T>()), T(2.5))    , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(4.9), eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(eve::inf(eve::as<T>()), T(2.5))   , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(4.9),eve::inf(eve::as<T>()))      , eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(eve::minf(eve::as<T>()), T(2.5))   , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(4.9),eve::minf(eve::as<T>()))     , eve::nan(eve::as<T>()), 0);
  }

  ulp = 70.0;
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T( 20),   T(2.0))   , T(420), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(10, T(0.1))         , T(1.253198719801548e+00), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(5,  T(0.1))         , T(1.163823072432015e+00) , ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(0,  T(0.1))         , T(0) , ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(2,  T(0.1))         , T(1.046485846853560e+00) , ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(20.3), T(10.2))   , T(1.622459238800527e+14), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20),  T(-2.0))   , T(2.164502164502165e-03), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(20),  T(-20))     , T(eve::tgamma(T(21))), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20),  T(20))     , eve::inf(eve::as<T>()), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20),  T(10.3))   , eve::zero(eve::as<T>()), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20.2),  T(-10.3)), T(1.780471883652420e-15), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20.2),  T( 10.3)), T(-2.953299835634237e+12), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20.2),  T( 30.4)), T(-4.755869905739260e+23), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(5), 10*eve::eps(eve::as<T>())), T(1.000000000000003e+00), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20.5),  T(-1.0))   , T(-4.651162790697673e-02), ulp);

  TTS_ULP_EQUAL(eve::diff_2nd(eve::rising_factorial)(T( 20),   T(2.0))   , T(1.288620076741702e+03), ulp);
  TTS_ULP_EQUAL(eve::diff_1st(eve::rising_factorial)(T( 20),   T(2.0))   , T(4.100000000000004e+01), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_2nd)(eve::rising_factorial)(T( 20),   T(2.0))   , T(1.288620076741702e+03), ulp);
  TTS_ULP_EQUAL(               eve::diff_2nd(eve::rising_factorial)(T( 20),   T(2.0))   , T(1.288620076741702e+03), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_1st)(eve::rising_factorial)(T( 20),   T(2.0))   , T(4.100000000000004e+01), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_1st)(eve::rising_factorial)(T(20.0), T(2.0)) , T(4.100000000000004e+01), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::diff_1st)(eve::rising_factorial)(T(-20.2),   T(2.0))   , T(-39.399999999999522515), ulp);
  TTS_ULP_EQUAL(eve::diff_1st(eve::rising_factorial)(T(-20.2),   T(2.0))   , eve::nan(eve::as<T>()), ulp);
};
