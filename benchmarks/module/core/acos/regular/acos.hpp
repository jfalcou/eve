//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acos.hpp>
#include <cmath>

#define REGISTER_BENCHMARK(FUNC, TYPE, ...)                                                         \
eve::bench::experiment  AS_UNIQUE(bench)                                                            \
                        ( std::string(AS_STRING(FUNC)) + " - " + ::tts::type_id<TYPE>()             \
                        , FUNC, eve::bench::optimal_size<TYPE>, __VA_ARGS__                         \
                        )                                                                           \
/**/

int main(int argc, char** argv)
{
  REGISTER_BENCHMARK(eve::acos, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

  eve::bench::start_benchmarks(argc, argv);
}
