//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/rotl.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  using I_TYPE    = eve::as_integer_t<EVE_TYPE>;
  using EVE_VALUE = eve::element_type_t<EVE_TYPE>;
  using I_VALUE   = eve::as_integer_t<EVE_VALUE>;
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  auto smin = I_VALUE(0);
  auto smax = I_VALUE(sizeof(EVE_VALUE)-1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<I_VALUE>(smin,smax);

  eve::bench::experiment xp;
  run<eve::bench::types<EVE_VALUE, I_VALUE>>(EVE_NAME(rotl) , xp, eve::rotl, arg0, arg1);
  run<eve::bench::types<EVE_TYPE,  I_VALUE>> (EVE_NAME(rotl) , xp, eve::rotl, arg0, arg1);
  run<eve::bench::types<EVE_TYPE,  I_TYPE>> (EVE_NAME(rotl) , xp, eve::rotl, arg0, arg1);


}
