//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/csch.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::minlog(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::maxlog(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__csch = [](auto x){return 1/std::sinh(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__csch) , xp, std__csch , arg0);
  run<EVE_VALUE>(EVE_NAME(csch) , xp, eve::csch , arg0);
  run<EVE_TYPE> (EVE_NAME(csch) , xp, eve::csch , arg0);

}
