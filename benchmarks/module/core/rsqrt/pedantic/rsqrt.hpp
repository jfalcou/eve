//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/math/constant/oneotwoeps.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <cmath>

int main()
{
  auto lmax = [](){
    if constexpr(eve::floating_value<EVE_VALUE>) return eve::oneotwoeps(eve::as<EVE_VALUE>());
    else return eve::valmax(eve::as<EVE_VALUE>());
  }();
  auto lmin = EVE_VALUE(0);

  auto const std__rsqrt = [](EVE_VALUE x) { return EVE_VALUE(1/std::sqrt(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__rsqrt) , xp, std__rsqrt, arg0);
  run<EVE_VALUE> (EVE_NAME(eve::pedantic(eve::rsqrt)) , xp, eve::pedantic(eve::rsqrt), arg0);
  run<EVE_TYPE>  (EVE_NAME(eve::pedantic(eve::rsqrt)) , xp, eve::pedantic(eve::rsqrt), arg0);
}
