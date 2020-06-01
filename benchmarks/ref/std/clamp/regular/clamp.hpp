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
#include <algorithm>

int main(int argc, char** argv)
{
  auto const std_clamp = [](auto x, auto y, auto z) { return std::clamp(x, y, EVE_TYPE(y+z)); };
  auto lmin = eve::Valmin<EVE_TYPE>();
  auto lmax = eve::Valmax<EVE_TYPE>();
  auto lmax2 = EVE_TYPE(lmax/2);
  EVE_REGISTER_BENCHMARK(std_clamp, EVE_TYPE
                        , eve::bench::random< EVE_TYPE>(lmin, lmax)
                        , eve::bench::random< EVE_TYPE>(lmin, lmax2)
                        , eve::bench::random< EVE_TYPE>(EVE_TYPE(0), lmax2));

  eve::bench::start_benchmarks(argc, argv);
}
