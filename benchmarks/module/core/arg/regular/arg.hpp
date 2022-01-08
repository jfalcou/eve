//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/arg.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>


int main()
{
  using EVE_VALUE = eve::element_type_t<EVE_TYPE>;
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(arg) , xp, eve::arg, arg0);
  run<EVE_TYPE>  (EVE_NAME(arg) , xp, eve::arg, arg0);
}
