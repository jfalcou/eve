//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <numbers>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>

int main(int argc, char** argv)
{
  constexpr EVE_TYPE indeg = EVE_TYPE(180)/std::numbers::pi_v<EVE_TYPE>;
  auto const std_atand = [indeg](auto x) { return indeg*std::atan(x); };
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());

  EVE_REGISTER_BENCHMARK(std_atand, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
