//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1);
  auto lmax = EVE_VALUE(1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asind = [](auto x){return  eve::radindeg(std::asin(x));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__asind) , xp, std__asind , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::asind) , xp, eve::asind , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::asind) , xp, eve::asind , arg0);
}
