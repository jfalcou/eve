//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lrising_factorial.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_result.h>

extern "C" {
  double gsl_sf_lnpoch(double, double);
  int gsl_sf_lnpoch_sgn_e(double, double, gsl_sf_result*, double*);
};

TTS_CASE_TPL("Check eve::lrising_factorial return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw(eve::lrising_factorial)(int(), T()), T);
}

TTS_CASE_TPL("Check eve::lrising_factorial behavior", EVE_TYPE)
{
  auto gsl_lnr = [](auto a, auto x){
   gsl_sf_result res;
   double sgn;
   gsl_sf_lnpoch_sgn_e(a, x, &res, &sgn);
   return res.val;
  };
  auto ulp = sizeof(eve::element_type_t<T>) == 4 ? 70 : 20;
  TTS_ULP_EQUAL(eve::lrising_factorial(T( 20),   T(2.0)) , T(gsl_lnr( 20.,  2.)), ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(10, T(0.1)) , T(gsl_lnr(10.0, 0.1)), ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(5,  T(0.1)) , T(gsl_lnr(5.0, 0.1)) , ulp);
//  TTS_ULP_EQUAL(eve::lrising_factorial)(0,  T(0.1)) , T(gsl_lnr(0.0, 0.1)) , ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(0,  T(0.1)) , eve::nan(eve::as<T>()), ulp);
//  TTS_ULP_EQUAL(eve::lrising_factorial)(1,  T(0.1)) , T(gsl_lnr(1.0, 0.1)) , 20);
  TTS_ULP_EQUAL(eve::lrising_factorial(T(20.3), T(10.2)) , T(gsl_lnr(20.3, 10.2)), 20);
  TTS_ULP_EQUAL(eve::lrising_factorial(T(-20),  T(-2.0)) , eve::nan(eve::as<T>()), ulp);


//   TTS_ULP_EQUAL(eve::lrising_factorial(T(20),  T(-20))   , T(gsl_lnr(20., -20.)), 20);
//   TTS_ULP_EQUAL(eve::lrising_factorial(T(-20),  T(20))   , eve::nan(eve::as<T>()), 20);
//   TTS_ULP_EQUAL(eve::lrising_factorial(T(0), T(10))      , T(gsl_lnr(0., 10.)), 20);
//   TTS_ULP_EQUAL(eve::lrising_factorial(T(10), T(0))      , T(gsl_lnr(10., 0.)), 20);
//  TTS_ULP_EQUAL(eve::lrising_factorial(T(-10.3), T(-5.2)), T(gsl_lnr(-10.3, -5.2)), 20);
  //lgamma doit etre verolé en négatif
}
