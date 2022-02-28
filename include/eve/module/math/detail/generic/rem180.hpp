//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>
//#include <eve/module/math/regular/quadrant.hpp>

namespace eve::detail
{
  template <floating_real_value T>
  EVE_FORCEINLINE auto  rem180(T x) noexcept
  {
//     std::cout << std::setprecision(15) << "x " << x << std::endl;
    T xi = nearest(2*div_180(x));
//       std::cout << "xi " << xi << std::endl;
    x = fma(xi, T(-90), x);
//       std::cout << "x " << x << " no change =  " << (x == x_180) << std::endl;
//       auto [fn, xr, dxr] = rem2(div_180(x));

//       std::cout << "fn  " << fn << std::endl;
//       std::cout << "xr  " << xr << std::endl;
//       std::cout << "dxr " << dxr << std::endl;
//       {
    T fn = quadrant(xi);
    T xr = x;
//    T dxr(0);
    auto tst = x >= 45;
    xr = if_else(tst, xr-T(45), xr);
//    fn= if_else(tst, fn+1, fn);
    tst = xr >= 45;
    xr = if_else(tst, xr-T(45), xr);
//    fn= if_else(tst, fn+1, fn);
    tst = xr >= 45;
    xr = if_else(tst, x-T(45), xr);
//    fn= if_else(tst, fn+1, fn);
//     std::cout << "xr  " << xr << std::endl;

    xr = div_180(xr) *pi(as(xr));
//    std::cout << "fn  " << fn << std::endl;
//    std::cout << "xr  " << xr << std::endl;
//    }

    return kumi::make_tuple(fn, xr, zero(as(xr)));
  }
}
