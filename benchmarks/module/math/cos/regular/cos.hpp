//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::Valmin<EVE_VALUE>());
  auto lmax = EVE_VALUE(eve::Valmax<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__cos = [](auto x){return std::cos(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__cos) , xp, std__cos , arg0);
  run<EVE_VALUE>(EVE_NAME(cos) , xp, eve::cos , arg0);
  run<EVE_TYPE> (EVE_NAME(cos) , xp, eve::cos , arg0);

}
