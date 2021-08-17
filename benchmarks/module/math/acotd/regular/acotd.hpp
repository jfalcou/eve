//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/acotd.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-5);
  auto lmax = EVE_VALUE(5);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__acotd = [](auto x){return std::atan(1/x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__acotd) , xp, std__acotd , arg0);
  run<EVE_VALUE>(EVE_NAME(acotd) , xp, eve::acotd , arg0);
  run<EVE_TYPE> (EVE_NAME(acotd) , xp, eve::acotd , arg0);
}
