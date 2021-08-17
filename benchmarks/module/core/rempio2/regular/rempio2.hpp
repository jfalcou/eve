//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/rempio2.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1000000);
  auto lmax = EVE_VALUE(1000000);

  auto const std__rempio2 = [](EVE_VALUE x) { return eve::rem_pio2(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__rempio2) , xp, std__rempio2, arg0);
  run<EVE_VALUE> (EVE_NAME(big_(rempio2)) , xp, eve::big_(eve::rempio2), arg0);
  run<EVE_TYPE>  (EVE_NAME(big_(rempio2)) , xp, eve::big_(eve::rempio2), arg0);
  run<EVE_VALUE>  (EVE_NAME(medium_(rempio2)) , xp, eve::medium_(eve::rempio2), arg0);
  run<EVE_TYPE>  (EVE_NAME(medium_(rempio2)) , xp, eve::medium_(eve::rempio2), arg0);
}
