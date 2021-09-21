//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/is_flint.hpp>
#include <eve/function/abs.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxflint.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__is_flint = [](EVE_VALUE x) -> eve::logical<EVE_VALUE>
    { return (eve::abs(x) < eve::maxflint(eve::as<EVE_VALUE>())) && !(x-std::trunc(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_flint) , xp, std__is_flint, arg0);
  run<EVE_VALUE> (EVE_NAME(pedantic(eve::is_flint)) , xp, eve::pedantic(eve::is_flint), arg0);
  run<EVE_TYPE>  (EVE_NAME(pedantic(eve::is_flint)) , xp, eve::pedantic(eve::is_flint), arg0);
}
