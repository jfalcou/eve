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
  EVE_VALUE mid = sizeof(EVE_VALUE) == 4 ? 2 : 5;
  {
    auto lmin = EVE_VALUE(0);
    auto lmax = EVE_VALUE(mid);

    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    auto stdj0 = [](auto x){return std::cyl_bessel_j(0, x);};
    auto boostj0= [](auto x){return boost::math::detail::bessel_j0(x);};
    eve::bench::experiment xp;
    run<EVE_TYPE> (EVE_NAME(cyl_bessel_j0_small) , xp, eve::cyl_bessel_j0 , arg0);
    run<EVE_VALUE>(EVE_NAME(cyl_bessel_j0_small) , xp, eve::cyl_bessel_j0 , arg0);
    run<EVE_VALUE>(EVE_NAME(stdj0_small) , xp, stdj0 , arg0);
    run<EVE_VALUE>(EVE_NAME(boostj0_small), xp, boostj0 , arg0);
  }
  {
    auto lmin = EVE_VALUE(mid);
    auto lmax = EVE_VALUE(8);

    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    auto stdj0 = [](auto x){return std::cyl_bessel_j(0, x);};
    auto boostj0= [](auto x){return boost::math::detail::bessel_j0(x);};
    eve::bench::experiment xp;
    run<EVE_TYPE> (EVE_NAME(cyl_bessel_j0_medium) , xp, eve::cyl_bessel_j0 , arg0);
    run<EVE_VALUE>(EVE_NAME(cyl_bessel_j0_medium) , xp, eve::cyl_bessel_j0 , arg0);
    run<EVE_VALUE>(EVE_NAME(stdj0_medium) , xp, stdj0 , arg0);
    run<EVE_VALUE>(EVE_NAME(boostj0_medium), xp, boostj0 , arg0);
  }
  {
    auto lmin = EVE_VALUE(8);
    auto lmax = EVE_VALUE(10000);

    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    auto stdj0 = [](auto x){return std::cyl_bessel_j(0, x);};
    auto boostj0= [](auto x){return boost::math::detail::bessel_j0(x);};
    eve::bench::experiment xp;
    run<EVE_TYPE> (EVE_NAME(cyl_bessel_j0_large) , xp, eve::cyl_bessel_j0 , arg0);
    run<EVE_VALUE>(EVE_NAME(cyl_bessel_j0_large) , xp, eve::cyl_bessel_j0 , arg0);
    run<EVE_VALUE>(EVE_NAME(stdj0_large) , xp, stdj0 , arg0);
    run<EVE_VALUE>(EVE_NAME(boostj0_large), xp, boostj0 , arg0);
  }
  {
    auto lmin = EVE_VALUE(0);
    auto lmax = EVE_VALUE(11);

    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    auto stdj0 = [](auto x){return std::cyl_bessel_j(0, x);};
    auto boostj0= [](auto x){return boost::math::detail::bessel_j0(x);};
    eve::bench::experiment xp;
    run<EVE_TYPE> (EVE_NAME(cyl_bessel_j0_mixed) , xp, eve::cyl_bessel_j0 , arg0);
    run<EVE_VALUE>(EVE_NAME(cyl_bessel_j0_mixed) , xp, eve::cyl_bessel_j0 , arg0);
    run<EVE_VALUE>(EVE_NAME(stdj0_mixed) , xp, stdj0 , arg0);
    run<EVE_VALUE>(EVE_NAME(boostj0_mixed), xp, boostj0 , arg0);
  }
}
