//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/logical.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  using L_TYPE = eve::logical<EVE_TYPE>;
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
  auto std_inc = [](auto c, auto e){return (e != eve::valmax(eve::as<EVE_TYPE>()) && c) ? e+1 : e; };
  EVE_REGISTER_BENCHMARK(std_inc, EVE_TYPE
                        , eve::bench::random<L_TYPE>(0,1)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
