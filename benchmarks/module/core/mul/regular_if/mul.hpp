//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE = eve::logical<EVE_TYPE>;

  auto arg0 = eve::bench::bernoulli_<EVE_VALUE>();
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg2 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto eve__mul =  [](auto x,  auto y,  auto z){ return eve::mul[x](y, z); };

  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE, EVE_VALUE>>(EVE_NAME( eve_mul) , xp, eve__mul, arg0, arg1, arg2);
  run<eve::bench::types<L_TYPE, EVE_TYPE, EVE_TYPE>> (EVE_NAME( eve_mul) , xp, eve__mul, arg0, arg1, arg2);
}
