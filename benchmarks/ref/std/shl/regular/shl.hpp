//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_shl = [](auto x, auto y) { return EVE_TYPE(x << y); };
  auto lmin1 = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax1 = eve::valmax(eve::as<EVE_TYPE>());
  auto lmin2 = EVE_TYPE(0);
  auto lmax2 = EVE_TYPE(sizeof(EVE_TYPE)-1);
  EVE_REGISTER_BENCHMARK(std_shl, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin1,lmax1)
                        , eve::bench::random<EVE_TYPE>(lmin2,lmax2));

  eve::bench::start_benchmarks(argc, argv);
}
