//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <bit>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main(int argc, char** argv)
{
  auto const std_bit_floor = [](auto x) { return std::bit_floor(x); };
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_bit_floor, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
