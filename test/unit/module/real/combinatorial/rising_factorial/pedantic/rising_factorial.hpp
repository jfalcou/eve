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
#include <gsl/gsl_math.h>

extern "C" {
  double gsl_sf_poch(double, double);
};

TTS_CASE_TPL("Check eve::rising_factorial return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::rising_factorial)(int(), T()), T);
  TTS_EXPR_IS(eve::pedantic(eve::rising_factorial)( T (), T()), T);
}

TTS_CASE_TPL("Check eve::rising_factorial behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;
  auto gsl_r = [](auto a, auto x){
    return gsl_sf_poch(a, x);
  };
  auto ulp = sizeof(eve::element_type_t<T>) == 4 ? 70 : 70;
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T( 20),   T(2.0))   , T(gsl_r( 20.,  2.)), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(10, T(0.1))         , T(gsl_r(10.0, 0.1)), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(5,  T(0.1))         , T(gsl_r(5.0, 0.1)) , ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(0,  T(0.1))         , T(gsl_r(0.0, 0.1)) , ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(0,  T(0.1))         ,  T(gsl_r(0.0, 0.1)) , ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(2,  T(0.1))         , T(gsl_r(2.0, 0.1)) , ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(20.3), T(10.2))   , T(gsl_r(20.3, 10.2)), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20),  T(-2.0))   , T(gsl_r(-20., -2.0)), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(20),  T(-20))     , T(eve::tgamma(T(21))), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20),  T(20))     , eve::inf(eve::as<T>()), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20),  T(10.3))   , eve::zero(eve::as<T>()), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20.2),  T(-10.3)), T(gsl_r(-20.2, -10.3)), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20.2),  T(-10.3)), T(gsl_r(-20.2, -10.3)), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20.2),  T( 10.3)), T(gsl_r(-20.2, 10.3)), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20.2),  T( 30.4)), T(gsl_r(-20.2, 30.4)), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(5), 10*eve::eps(eve::as<T>())), T(gsl_r(5.0,  10*eve::eps(eve::as<elt_t>()))), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::rising_factorial)(T(-20.5),  T(-1.0))   , T(gsl_r(-20.5, -1.0)), ulp);
}
