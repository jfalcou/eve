//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>
#include <eve/constant/true.hpp>
#include <cmath>

int main()
{
  using I_TYPE = eve::logical<EVE_TYPE>;
  EVE_REGISTER_BENCHMARK(eve::mul, EVE_TYPE
                        , eve::bench::random<I_TYPE>(0, 1)
                        , eve::bench::random<EVE_TYPE>(-1.,1.)
                        , eve::bench::random<EVE_TYPE>(-1.,1.));

}
