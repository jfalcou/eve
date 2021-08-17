//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>

int main(int argc, char** argv)
{
  auto const std_asinh = [](auto x) { return std::asinh(x); };
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());

  EVE_REGISTER_BENCHMARK(std_asinh, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
