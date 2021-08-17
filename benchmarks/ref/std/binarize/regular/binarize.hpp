//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <numbers>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main(int argc, char** argv)
{
  auto const std_binarize = [](auto x) { return x ? EVE_TYPE(1) : EVE_TYPE(0); };
  auto const std_binarize2= [](auto x, auto y){ return x ? EVE_TYPE(y) : EVE_TYPE(0); };
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());

  EVE_REGISTER_BENCHMARK(std_binarize, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));
  EVE_REGISTER_BENCHMARK(std_binarize2, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin, lmax)
                        , eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
