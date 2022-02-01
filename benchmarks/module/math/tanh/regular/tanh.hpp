//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/tanh.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/math/constant/minlog.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::minlog(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::maxlog(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__tanh = [](auto x){return std::tanh(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__tanh) , xp, std__tanh , arg0);
  run<EVE_VALUE>(EVE_NAME(tanh) , xp, eve::tanh , arg0);
  run<EVE_TYPE> (EVE_NAME(tanh) , xp, eve::tanh , arg0);

}
