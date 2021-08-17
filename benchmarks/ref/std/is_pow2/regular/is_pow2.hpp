//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <bit>

int main(int argc, char** argv)
{
  auto const std_is_pow2 = [](auto x) { return std::has_single_bit(x); };

  EVE_REGISTER_BENCHMARK(std_is_pow2, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

  eve::bench::start_benchmarks(argc, argv);
}
