//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/bessel.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

int main()
{
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(11);
  auto lmin1 = EVE_VALUE(0);
  auto lmax1 = EVE_VALUE(100);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1= eve::bench::random_<EVE_VALUE>(lmin1,lmax1);
  auto stdjn   = [](auto n, auto x){return std::cyl_bessel_j(n, x);};
  auto boostjn = [](auto n, auto x){return boost::math::cyl_bessel_j(n, x);};
  eve::bench::experiment xp;
  run<EVE_TYPE> (EVE_NAME(cyl_bessel_jn) , xp, eve::cyl_bessel_jn , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(cyl_bessel_jn) , xp, eve::cyl_bessel_jn , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(stdjn), xp, stdjn , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(boostjn), xp, boostjn , arg0, arg1);
}
