//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE = eve::logical<EVE_TYPE>;

  auto arg00 = eve::bench::random_<EVE_VALUE>(0, 1);
  auto arg0 = eve::bench::random_<L_VALUE>(0, 1);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg2 = eve::bench::random_<EVE_VALUE>(EVE_VALUE(1),lmax);

  auto eve__div =  [](auto x,  auto y,  auto z){ return eve::div[x](y, z); };

  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE, EVE_VALUE>>(EVE_NAME( eve_div) , xp, eve__div, arg0, arg1, arg2);
  run<eve::bench::types<L_TYPE, EVE_TYPE, EVE_TYPE>> (EVE_NAME( eve_div) , xp, eve__div, arg0, arg1, arg2);

  run<EVE_VALUE>(EVE_NAME( eve_div) , xp, eve__div, arg00, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME( eve_div) , xp, eve__div, arg00, arg1, arg2);

}
