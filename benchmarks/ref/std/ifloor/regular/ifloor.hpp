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
#include <eve/detail/meta/traits.hpp>

int main(int argc, char** argv)
{
  using I_TYPE =  eve::as_integer_t<EVE_TYPE>;
  auto const std_ifloor = [](auto x) { return static_cast<I_TYPE>(std::floor(x)); };
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_ifloor, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
