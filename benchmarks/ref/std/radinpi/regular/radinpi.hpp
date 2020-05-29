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
#include <numbers>

int main(int argc, char** argv)
{
  auto lmin = eve::Valmin<EVE_TYPE>();
  auto lmax = eve::Valmax<EVE_TYPE>();
  constexpr EVE_TYPE invpi = std::numbers::inv_pi_v<EVE_TYPE>;
  auto std_radinpi = [](auto x){return x*invpi; };
  EVE_REGISTER_BENCHMARK(std_radinpi, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
#
