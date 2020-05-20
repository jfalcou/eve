//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/binarize.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  using I_TYPE = eve::logical<EVE_TYPE>;
  using E_TYPE = eve::detail::value_type_t<EVE_TYPE>;
  EVE_REGISTER_BENCHMARK(eve::binarize, EVE_TYPE
                        , eve::bench::random<I_TYPE>(0, 1)
                        , eve::bench::random<E_TYPE>(-1.,1.));

  EVE_REGISTER_BENCHMARK(eve::binarize, EVE_TYPE
                        , eve::bench::random<I_TYPE>(0, 1));

  eve::bench::start_benchmarks(argc, argv);
}
