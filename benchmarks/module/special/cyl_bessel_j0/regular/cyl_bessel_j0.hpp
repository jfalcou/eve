//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

int main()
{
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(10);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
//  auto stdj0 = [](auto x){return std::cyl_bessel_j(0, x);};
  auto boostj0= [](auto x){return boost::math::detail::bessel_j0(x);};
  eve::bench::experiment xp;
  run<EVE_TYPE> (EVE_NAME(cyl_bessel_j0) , xp, eve::cyl_bessel_j0 , arg0);
  run<EVE_VALUE>(EVE_NAME(cyl_bessel_j0) , xp, eve::cyl_bessel_j0 , arg0);
//  run<EVE_VALUE>(EVE_NAME(stdj0) , xp, stdj0 , arg0);
  run<EVE_VALUE>(EVE_NAME(boostj0), xp, boostj0 , arg0);
}
