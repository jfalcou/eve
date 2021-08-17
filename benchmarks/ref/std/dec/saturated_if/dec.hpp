//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/logical.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  using L_TYPE = eve::logical<EVE_TYPE>;
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
  auto std_dec = [](auto c, auto e){return ((e != eve::valmin(eve::as<EVE_TYPE>()) && c)) ? e-1 : e; };
  EVE_REGISTER_BENCHMARK(std_dec, EVE_TYPE
                        , eve::bench::random<L_TYPE>(0,1)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
