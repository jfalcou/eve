//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/regular/cospi.hpp>
#include <eve/module/math/detail/generic/rem180.hpp>
namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_), quarter_circle_type const &, T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return eve::quarter_circle(cospi)(div_180(x));
    }
    else
      return apply_over(quarter_circle(cosd), x);
  }

  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  requires(is_one_of<D>(types<half_circle_type,full_circle_type, medium_type, big_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
        if( is_not_finite(a0) ) return nan(eve::as<T>());
      auto x = eve::abs(a0);

//       std::cout << std::setprecision(10) << "x " << x << std::endl;
//       T xi = nearest(div_180(x));
//       std::cout << "xi " << xi << std::endl;
//       x = fma(xi, T(-180), x);
// //       std::cout << "x " << x << " no change =  " << (x == x_180) << std::endl;
// //       auto [fn, xr, dxr] = rem2(div_180(x));

// //       std::cout << "fn  " << fn << std::endl;
// //       std::cout << "xr  " << xr << std::endl;
// //       std::cout << "dxr " << dxr << std::endl;
// //       {
//         T fn(0);
//         T xr = x;
//         T dxr(0);
//         auto tst = x >= 45;
//         xr = if_else(tst, xr-T(45), xr);
//         fn= if_else(tst, fn, fn+1);
//         tst = x >= 45;
//         xr = if_else(tst, xr-T(45), xr);
//         fn= if_else(tst, fn, fn+1);
//         tst = xr >= 45;
//         xr = if_else(tst, x-T(45), xr);
//         fn= if_else(tst, fn, fn+1);
//         xr = div_180(xr)*pi(as(xr));
//         std::cout << "fn2  " << fn << std::endl;
//         std::cout << "xr2  " << xr << std::endl;
//         std::cout << "dxr2 " << dxr << std::endl;
// //       }
      auto [fn, xr, dxr] = rem180(x);
      return cos_finalize(fn, xr, dxr);
    }
    else
      return apply_over(D()(cosd), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( eve::all(eve::abs(x) <= T(45)) )
        return quarter_circle(cosd)(x);
      else
        return big(cosd)(x);
    }
    else
      return apply_over(cosd, a0);
  }

 //  template<floating_real_value T, decorator D>
//   EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
//   {
//     if constexpr(has_native_abi_v<T>)
//     {
//       return D()(cospi)(div_180(a0));
//     }
//     else
//       return apply_over(D()(cosd), a0);
//   }

//   template<floating_real_value T>
//   EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
//   {
//     return cosd(regular_type(), a0);
//   }

}
