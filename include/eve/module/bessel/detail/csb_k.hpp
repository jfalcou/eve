//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/module/bessel/detail/kernel_bessel_y0.hpp>
#include <eve/module/bessel/detail/kernel_bessel_y1.hpp>
#include <eve/module/bessel/detail/kernel_bessel_y.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/as_element.hpp>

namespace eve::detail
{
  // T is always floating
  template < typename I,  typename T > constexpr EVE_FORCEINLINE
  T cb_k(I nu, T x) noexcept
  {
    if constexpr(floating_value<I>)
    {
      if constexpr(scalar_value<I> && simd_value<T>)
      {
        auto flintx = is_flint(nu);
        return flintx ? kernel_bessel_k_int(nu, x) : kernel_bessel_k_flt(T(nu), x);
      }  
      else if constexpr( scalar_value<T> )
      {
        auto flintx = is_flint(nu);
        return flintx ? kernel_bessel_k_int(nu, x) : kernel_bessel_k_flt(nu, x);
      }
      else // simd
      {
        auto flint_nu = is_flint(nu);
        if( eve::all(flint_nu) ) return kernel_bessel_k_int(nu, x);
        else if( eve::none(flint_nu) ) return kernel_bessel_k_flt(nu, x);
        else
        {
          auto nu_int = if_else(flint_nu, nu, zero);
          auto nu_flt = if_else(flint_nu, T(0.5), nu);
          return if_else(flint_nu, kernel_bessel_k_int(nu_int, x), kernel_bessel_k_flt(nu_flt, x));
        }
      }
    }
    else //if constexpr(integral_value<I>)
    {
      if constexpr(simd_value<I> && scalar_value<T>)
      {
        using c_t = wide<T, cardinal_t<I>>;
        return cyl_bessel_kn(nu, c_t(x));
      }
      else if constexpr(scalar_value<I> && scalar_value<T>)
      {
        return kernel_bessel_k_int(nu, x);
      }
      else if constexpr(scalar_value<I> && simd_value<T>)
      {
        using i_t = wide<I, cardinal_t<T>>;
        return kernel_bessel_k_int(i_t(nu), x);
      }
      else if constexpr(simd_value<I> && simd_value<T>)
      {
        auto n = convert(nu, as_element(x));
        return kernel_bessel_k_int(n, x);
      }
    }
  }

  // T is always floating
  template < typename I,  typename T > constexpr EVE_FORCEINLINE
  T sb_k(I n, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr( integral_value<I> ) return sb_k(convert(n, as<elt_t>()), x);
    else                              return cb_k(n + half(as(x)), x) * rsqrt(2 * x * inv_pi(as(x)));
   }
}
