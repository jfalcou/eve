//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main(int argc, char** argv)
{
  auto const std_frexp = [](auto x) { int e; auto m = std::frexp(x,  &e);
                                      return std::make_tuple(m, EVE_TYPE(e)); };
  auto l = eve::valmax(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_frexp, EVE_TYPE
                        , eve::bench::random< EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
