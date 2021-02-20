//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/rising_factorial.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <eve/constant/eps.hpp>

#include <type_traits>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::rising_factorial return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::rising_factorial)(int(), T()), T);
  TTS_EXPR_IS(eve::pedantic(eve::rising_factorial)( T (), T()), T);
}

TTS_CASE_TPL("Check eve::rising_factorial behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(eve::nan(eve::as<T>()), T(2.5))    , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(4.9), eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(eve::inf(eve::as<T>()), T(2.5))   , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(4.9),eve::inf(eve::as<T>()))      , eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(eve::minf(eve::as<T>()), T(2.5))   , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(4.9),eve::minf(eve::as<T>()))     , eve::nan(eve::as<T>()), 0);
  }

  auto ulp = 70.0;
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
}
