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
  T cb_i(I nu, T x) noexcept
  {
    if constexpr( integral_value<I> )
    {
      nu = eve::abs(nu);  //DLMF 10.27.1 I-n(z) = In(z),
      if constexpr( simd_value<I> && scalar_value<T> )
      {
        using c_t = wide<T, cardinal_t<I>>;
        return cb_i(convert(nu, as(x)), c_t(x));
      }
      else if constexpr( simd_value<I> && simd_value<T> )
      {
        using elt_t = element_type_t<T>;
        auto tnu    = convert(nu, as(elt_t()));
        return cb_i(tnu, x);
      }
      else if constexpr( integral_scalar_value<I> )
      {
        return cb_i(T(nu), x);
      }
    }
    else // I is floating
    {
      if constexpr( simd_value<I> && scalar_value<T> )
      {
        using c_t = wide<T, cardinal_t<I>>;
        return cb_i(nu, c_t(x));
      }
      else if constexpr( scalar_value<I> && simd_value<T> )
      {
        return cb_i(T(nu), x);
      }
      else
      {
        return kernel_bessel_i(nu, x);
      }
    }
  }

  // T is always floating
  template < typename I,  typename T > constexpr EVE_FORCEINLINE
  T sb_i(I n, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr( integral_value<I> ) return sb_i(convert(n, as<elt_t>()), x);
    else                              return cb_i(n + half(as(x)), x) * rsqrt(2 * x * inv_pi(as(x)));
   }
}
