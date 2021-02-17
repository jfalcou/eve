//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rising_factorial.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>
#include <gsl/gsl_math.h>

extern "C" {double gsl_sf_poch(double, double); };

// TTS_CASE_TPL("Check eve::rising_factorial return type", EVE_TYPE)
// {
//     TTS_EXPR_IS(eve::rising_factorial(int(), T()), T);
// }

TTS_CASE_TPL("Check eve::rising_factorial behavior", EVE_TYPE)
{
  std::cout << "test n " << 10 << " x " << T(0.1) << std::endl;
  TTS_ULP_EQUAL(eve::rising_factorial(10, T(0.1)) , T(gsl_sf_poch(0.1, 10.0)), 20);
  TTS_ULP_EQUAL(eve::rising_factorial(T(-10.2), T(-0.1))  ,  T(gsl_sf_poch(-0.1, -10.2)), 20);
//   TTS_ULP_EQUAL(eve::rising_factorial(5,  T(1)) , T(boost::math::rising_factorial(1.0, 5)) , 20);
//   TTS_ULP_EQUAL(eve::rising_factorial(0,  T(0.1)) , T(boost::math::rising_factorial(0.1, 0)) , 20);
//  TTS_ULP_EQUAL(eve::rising_factorial(1,  T(0.1)) , T(boost::math::rising_factorial(0.1, 1)) , 20);
}
