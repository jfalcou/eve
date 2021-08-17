//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numbers>

int main(int argc, char** argv)
{
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
  constexpr EVE_TYPE pi_180 = std::numbers::pi_v<EVE_TYPE>/180;
  auto std_radindeg = [pi_180](auto x){return x*pi_180; };
  EVE_REGISTER_BENCHMARK(std_radindeg, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
#
