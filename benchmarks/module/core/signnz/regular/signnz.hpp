//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/signnz.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__signnz = [](EVE_VALUE x) { return EVE_VALUE((0 <= x)-(0 > x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__signnz) , xp, std__signnz, arg0);
  run<EVE_VALUE> (EVE_NAME(signnz) , xp, eve::signnz, arg0);
  run<EVE_TYPE>  (EVE_NAME(signnz) , xp, eve::signnz, arg0);
}
