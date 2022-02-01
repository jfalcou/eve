//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/fms.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg2 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__fms =  [](EVE_VALUE x,  EVE_VALUE y, auto z){return EVE_VALUE(std::fma(x, y, -z)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__fms) , xp, std__fms, arg0, arg1, arg2);
  run<EVE_VALUE>(EVE_NAME(pedantic(eve::fms)) , xp, eve::pedantic(eve::fms), arg0, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME(pedantic(eve::fms)) , xp, eve::pedantic(eve::fms), arg0, arg1, arg2);
}
