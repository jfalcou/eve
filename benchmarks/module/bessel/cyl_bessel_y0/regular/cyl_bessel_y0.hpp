//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/bessel.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

int main()
{
  EVE_VALUE mid = sizeof(EVE_VALUE) == 4 ? 2 : 5;
  {
    auto lmin = EVE_VALUE(0);
    auto lmax = EVE_VALUE(mid);

    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    auto stdy0 = [](auto x){return std::cyl_neumann(0, x);};
    auto boosty0= [](auto x){return boost::math::cyl_neumann(0, x);};
    eve::bench::experiment xp;
    run<EVE_TYPE> (EVE_NAME(cyl_bessel_y0_small) , xp, eve::cyl_bessel_y0 , arg0);
    run<EVE_VALUE>(EVE_NAME(cyl_bessel_y0_small) , xp, eve::cyl_bessel_y0 , arg0);
    run<EVE_VALUE>(EVE_NAME(stdy0_small) , xp, stdy0 , arg0);
    run<EVE_VALUE>(EVE_NAME(boosty0_small), xp, boosty0 , arg0);
  }
  {
    auto lmin = EVE_VALUE(mid);
    auto lmax = EVE_VALUE(8);

    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    auto stdy0 = [](auto x){return std::cyl_neumann(0, x);};
    auto boosty0= [](auto x){return boost::math::cyl_neumann(0, x);};
    eve::bench::experiment xp;
    run<EVE_TYPE> (EVE_NAME(cyl_bessel_y0_medium) , xp, eve::cyl_bessel_y0 , arg0);
    run<EVE_VALUE>(EVE_NAME(cyl_bessel_y0_medium) , xp, eve::cyl_bessel_y0 , arg0);
    run<EVE_VALUE>(EVE_NAME(stdy0_medium) , xp, stdy0 , arg0);
    run<EVE_VALUE>(EVE_NAME(boosty0_medium), xp, boosty0 , arg0);
  }
  {
    auto lmin = EVE_VALUE(8);
    auto lmax = EVE_VALUE(10000);

    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    auto stdy0 = [](auto x){return std::cyl_neumann(0, x);};
    auto boosty0= [](auto x){return boost::math::cyl_neumann(0, x);};
    eve::bench::experiment xp;
    run<EVE_TYPE> (EVE_NAME(cyl_bessel_y0_large) , xp, eve::cyl_bessel_y0 , arg0);
    run<EVE_VALUE>(EVE_NAME(cyl_bessel_y0_large) , xp, eve::cyl_bessel_y0 , arg0);
    run<EVE_VALUE>(EVE_NAME(stdy0_large) , xp, stdy0 , arg0);
    run<EVE_VALUE>(EVE_NAME(boosty0_large), xp, boosty0 , arg0);
  }
  {
    auto lmin = EVE_VALUE(0);
    auto lmax = EVE_VALUE(11);

    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    auto stdy0 = [](auto x){return std::cyl_neumann(0, x);};
    auto boosty0= [](auto x){return boost::math::cyl_neumann(0, x);};
    eve::bench::experiment xp;
    run<EVE_TYPE> (EVE_NAME(cyl_bessel_y0_mixed) , xp, eve::cyl_bessel_y0 , arg0);
    run<EVE_VALUE>(EVE_NAME(cyl_bessel_y0_mixed) , xp, eve::cyl_bessel_y0 , arg0);
    run<EVE_VALUE>(EVE_NAME(stdy0_mixed) , xp, stdy0 , arg0);
    run<EVE_VALUE>(EVE_NAME(boosty0_mixed), xp, boosty0 , arg0);
  }
}
