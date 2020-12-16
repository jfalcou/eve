//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lcm.hpp>
#include <eve/constant/valmin.hpp>
#include <numeric>

TTS_CASE_TPL("Check eve::lcm return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::lcm(T(), T()), T);
}

TTS_CASE_TPL("Check eve::lcm behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::lcm(T(22), T( 10)) , T(110));
  TTS_EQUAL(eve::lcm(T(7), T( 5)) , T(35));
  TTS_EQUAL(eve::lcm(T(0), T(1)), T(std::lcm((0), (1))) );
  TTS_EQUAL(eve::lcm(T(1), T(0)), T(std::lcm((1), (0))) );
}
