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
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_rshl = [](auto x, auto y) { return y >  0 ? x >> y : x << -y; };
  auto lmin1 = eve::Valmin<EVE_TYPE>();
  auto lmax1 = eve::Valmax<EVE_TYPE>();
  EVE_TYPE lmin2 = std::max(0, -(int(sizeof(EVE_TYPE))-1));
  EVE_TYPE lmax2 = EVE_TYPE(sizeof(EVE_TYPE)-1);
  EVE_REGISTER_BENCHMARK(std_rshl, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin1,lmax1)
                        , eve::bench::random<EVE_TYPE>(lmin2,lmax2));

  eve::bench::start_benchmarks(argc, argv);
}
