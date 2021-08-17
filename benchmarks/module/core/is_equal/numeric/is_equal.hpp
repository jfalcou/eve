//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/numeric/is_equal.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__is_equal =  [](EVE_VALUE x,  EVE_VALUE y) -> eve::logical<EVE_VALUE> {return (x == y) || (x != x && y !=  y); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__is_equal) , xp, std__is_equal, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(is_equal) , xp, eve::is_equal, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(is_equal) , xp, eve::is_equal, arg0, arg1);
}
