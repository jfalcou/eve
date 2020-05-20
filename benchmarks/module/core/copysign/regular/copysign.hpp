//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/copysign.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  EVE_REGISTER_BENCHMARK(eve::copysign, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(eve::Valmin<EVE_VALUE<(), eve::Valmax<EVE_VALUE>()));


  eve::bench::start_benchmarks(argc, argv);
}
