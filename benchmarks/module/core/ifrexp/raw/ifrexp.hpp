//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/ifrexp.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  eve::bench::experiment xp;

  run<EVE_VALUE> (EVE_NAME(raw(eve::ifrexp)) , xp, eve::raw(eve::ifrexp), arg0);
  run<EVE_TYPE>  (EVE_NAME(raw(eve::ifrexp)) , xp, eve::raw(eve::ifrexp), arg0);
}
