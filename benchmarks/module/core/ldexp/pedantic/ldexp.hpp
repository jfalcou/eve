//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ldexp.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  using I_TYPE    = eve::detail::as_integer_t<EVE_TYPE>;
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  using I_VALUE   = eve::detail::value_type_t<EVE_VALUE>;
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  auto smin = I_VALUE(0);
  auto smax = I_VALUE(sizeof(EVE_VALUE)-1);

  EVE_REGISTER_BENCHMARK(eve::pedantic_(eve::ldexp), EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<I_VALUE>(smin,smax));

  auto vmin = I_TYPE(0);
  auto vmax = I_TYPE(sizeof(EVE_VALUE)-1);
  EVE_REGISTER_BENCHMARK(eve::pedantic_(eve::ldexp), EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<I_TYPE>(vmin,vmax));
}
