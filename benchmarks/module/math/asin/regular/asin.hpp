//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asin.hpp>
#include <cmath>

int main()
{
  EVE_REGISTER_BENCHMARK(eve::asin, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

}
