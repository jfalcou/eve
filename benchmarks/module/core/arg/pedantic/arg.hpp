//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/math.hpp>


int main()
{
  using EVE_VALUE = eve::element_type_t<EVE_TYPE>;
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(pedantic(eve::arg)) , xp, eve::pedantic(eve::arg), arg0);
  run<EVE_TYPE>  (EVE_NAME(pedantic(eve::arg)) , xp, eve::pedantic(eve::arg), arg0);
}
