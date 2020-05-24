//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  using L_TYPE = eve::logical<EVE_TYPE>;
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  auto fl = [](auto a,  auto b){ return eve::if_else(a, b, eve::allbits_); };
  EVE_REGISTER_BENCHMARK(fl, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  EVE_REGISTER_BENCHMARK(fl, EVE_TYPE
                        , eve::bench::random<L_TYPE>(0, 1)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));
  auto fr = [](auto a,  auto b){ return eve::if_else(a, eve::allbits_, b); };

  EVE_REGISTER_BENCHMARK(fr, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  EVE_REGISTER_BENCHMARK(fr, EVE_TYPE
                        , eve::bench::random<L_TYPE>(0, 1)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));
 eve::bench::start_benchmarks(argc, argv);
}
