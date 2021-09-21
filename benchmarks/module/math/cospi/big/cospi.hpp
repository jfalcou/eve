//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cospi.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::valmin(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(big(eve::cospi)) , xp, eve::big(eve::cospi) , arg0);
  run<EVE_TYPE> (EVE_NAME(big(eve::cospi)) , xp, eve::big(eve::cospi) , arg0);

}
