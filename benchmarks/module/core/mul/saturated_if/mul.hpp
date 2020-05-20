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
#include <cmath>

int main(int argc, char** argv)
{
  using I_TYPE = eve::logical<EVE_TYPE>;
  auto f = [](auto c, auto a, auto b) { return eve::saturated_(eve::mul[c])(a,b);};
  EVE_REGISTER_BENCHMARK(f, EVE_TYPE
                        , eve::bench::random<I_TYPE>(0,1)
                        , eve::bench::random<EVE_TYPE>(-1.,1.)
                        , eve::bench::random<EVE_TYPE>(-1.,1.));

  eve::bench::start_benchmarks(argc, argv);
}
