//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/ulpdist.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);


  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(ulpdist) , xp, eve::ulpdist, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(ulpdist) , xp, eve::ulpdist, arg0, arg1);
}
