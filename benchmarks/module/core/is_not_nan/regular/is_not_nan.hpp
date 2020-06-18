//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_nan.hpp>
#include <cmath>

int main()
{
  EVE_REGISTER_BENCHMARK(eve::is_not_nan, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

}
