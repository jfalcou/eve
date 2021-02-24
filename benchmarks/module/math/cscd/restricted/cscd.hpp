//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscd.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/radindeg.hpp>

int main()
{
  auto lmax = EVE_VALUE(45);
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(restricted(eve::cscd)) , xp, eve::restricted(eve::cscd) , arg0);
  run<EVE_TYPE> (EVE_NAME(restricted(eve::cscd)) , xp, eve::restricted(eve::cscd) , arg0);
}
