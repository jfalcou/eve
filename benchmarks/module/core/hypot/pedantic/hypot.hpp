//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/hypot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  EVE_REGISTER_BENCHMARK(eve::pedantic_(eve::hypot), EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        );

  EVE_REGISTER_BENCHMARK(eve::pedantic_(eve::hypot), EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        );

}
