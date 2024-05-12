//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/bessel.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

int main()
{
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(10);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
//  auto stdj1 = [](auto x){return std::cyl_bessel_j(0, x);};
  auto boostj1= [](auto x){return boost::math::detail::bessel_j1(x);};
  eve::bench::experiment xp;
  run<EVE_TYPE> (EVE_NAME(cyl_bessel_j1) , xp, eve::cyl_bessel_j1 , arg0);
  run<EVE_VALUE>(EVE_NAME(cyl_bessel_j1) , xp, eve::cyl_bessel_j1 , arg0);
//  run<EVE_VALUE>(EVE_NAME(stdj1) , xp, stdj1 , arg0);
  run<EVE_VALUE>(EVE_NAME(boostj1), xp, boostj1 , arg0);
}
