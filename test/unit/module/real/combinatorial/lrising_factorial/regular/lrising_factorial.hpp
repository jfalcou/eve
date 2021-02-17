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

TTS_CASE_TPL("Check eve::lrising_factorial return type", EVE_TYPE)
{
    TTS_EXPR_IS(eve::lrising_factorial(int(), T()), T);
}

TTS_CASE_TPL("Check eve::lrising_factorial behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::lrising_factorial(10, T(0.1)) , T(boost::math::lrising_factorial(0.1, 10)), 20);
  TTS_ULP_EQUAL(eve::lrising_factorial(5,  T(0.1)) , T(boost::math::lrising_factorial(0.1, 5)) , 20);
  TTS_ULP_EQUAL(eve::lrising_factorial(0,  T(0.1)) , T(boost::math::lrising_factorial(0.1, 0)) , 20);
  TTS_ULP_EQUAL(eve::lrising_factorial(1,  T(0.1)) , T(boost::math::lrising_factorial(0.1, 1)) , 20);
}
