//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main(int argc, char** argv)
{
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
   auto const std_is_nez = [](auto x) { return x != 0; };
   EVE_REGISTER_BENCHMARK(std_is_nez, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
