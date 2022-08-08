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
  using L_VALUE = eve::logical<EVE_VALUE>;
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__is_ordered =  [](EVE_VALUE x,  EVE_VALUE y) -> eve::logical<EVE_VALUE> {return L_VALUE(!std::isunordered(x, y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__is_ordered) , xp, std__is_ordered, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(is_ordered) , xp, eve::is_ordered, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(is_ordered) , xp, eve::is_ordered, arg0, arg1);
}
