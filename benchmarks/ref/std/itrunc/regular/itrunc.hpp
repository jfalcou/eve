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
#include <eve/detail/meta/traits.hpp>

int main(int argc, char** argv)
{
  using I_TYPE =  eve::as_integer_t<EVE_TYPE>;
  auto const std_itrunc = [](auto x) { return static_cast<I_TYPE>(std::trunc(x)); };
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_itrunc, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
