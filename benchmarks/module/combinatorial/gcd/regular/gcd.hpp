//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/as_element.hpp>
#include <eve/module/combinatorial.hpp>
#include <numeric>

int main()
{
  auto lmin = 1;
  auto lmax = 100;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__gcd =  [](auto x,  auto y){return std::gcd(eve::convert(x, eve::int_from<decltype(x)>()), eve::convert(y, eve::int_from<decltype(y)>())); };
  auto eve__gcd =  [](auto x,  auto y){return eve::gcd(eve::trunc(x), eve::trunc(y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__gcd) , xp, std__gcd, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(gcd) , xp, eve__gcd, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(gcd) , xp, eve__gcd, arg0, arg1);
}
