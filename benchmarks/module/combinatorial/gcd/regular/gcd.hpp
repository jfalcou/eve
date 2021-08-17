//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/gcd.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/converter.hpp>
#include <numeric>

int main()
{
  auto lmin = 1; //eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = 100; //eve::valmax(eve::as<EVE_VALUE>());
//   if constexpr(std::is_floating_point_v<EVE_VALUE>)
//   {
//     lmin = -100000;
//     lmax =  100000;
//   }


  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__gcd =  [](auto x,  auto y){return std::gcd(eve::int_(x), eve::int_(y)); };
  auto eve__gcd =  [](auto x,  auto y){return eve::gcd(eve::trunc(x), eve::trunc(y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__gcd) , xp, std__gcd, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(gcd) , xp, eve__gcd, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(gcd) , xp, eve__gcd, arg0, arg1);
}
