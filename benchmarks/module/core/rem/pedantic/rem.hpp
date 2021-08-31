//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/rem.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(EVE_VALUE(1),lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(pedantic(eve::rem)) , xp, eve::pedantic(eve::rem), arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(pedantic(eve::rem)) , xp, eve::pedantic(eve::rem), arg0, arg1);
}
