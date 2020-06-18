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
#include <eve/function/pow_abs.hpp>

int main()
{
  auto const my_pow_abs = [](auto x, auto y) { return eve::raw_(eve::pow_abs)(x, y); };
  auto lmin = EVE_TYPE(-10);
  auto lmax = EVE_TYPE(10);
  EVE_REGISTER_BENCHMARK(my_pow_abs, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

}
