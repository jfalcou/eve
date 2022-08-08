//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__nextafter =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(std::nextafter(x, y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__nextafter) , xp, std__nextafter, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(nextafter) , xp, eve::nextafter, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(nextafter) , xp, eve::nextafter, arg0, arg1);
}
