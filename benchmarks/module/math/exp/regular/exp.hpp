//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/math/constant/minlog.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::minlog(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::maxlog(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__exp = [](auto x){return std::exp(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__exp) , xp, std__exp , arg0);
  run<EVE_VALUE>(EVE_NAME(exp) , xp, eve::exp , arg0);
  run<EVE_TYPE> (EVE_NAME(exp) , xp, eve::exp , arg0);

}
