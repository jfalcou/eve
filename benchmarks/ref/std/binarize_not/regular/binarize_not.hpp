//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <cmath>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main(int argc, char** argv)
{
  auto const std_binarize_not = [](auto x) { return x ? EVE_TYPE(0) : EVE_TYPE(1); };
  auto const std_binarize_not2= [](auto x, auto y){ return x ? EVE_TYPE(0) : EVE_TYPE(1); };
  auto lmin = eve::Valmin<EVE_TYPE>();
  auto lmax = eve::Valmax<EVE_TYPE>();

  EVE_REGISTER_BENCHMARK(std_binarize_not, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));
  EVE_REGISTER_BENCHMARK(std_binarize_not2, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin, lmax)
                        , eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
