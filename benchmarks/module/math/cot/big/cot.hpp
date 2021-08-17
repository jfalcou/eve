//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1000); //eve::valmin(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(1000); //eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__cot = [](auto x){return std::tan(1/x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__cot) , xp, std__cot , arg0);
  run<EVE_VALUE>(EVE_NAME(big(eve::cot)) , xp, eve::big(eve::cot) , arg0);
  run<EVE_TYPE> (EVE_NAME(big(eve::cot)) , xp, eve::big(eve::cot) , arg0);

}
