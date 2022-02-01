//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/max.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__max =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(std::max(x, y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__max) , xp, std__max, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(pedantic(eve::max)) , xp, eve::pedantic(eve::max), arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(pedantic(eve::max)) , xp, eve::pedantic(eve::max), arg0, arg1);
}
