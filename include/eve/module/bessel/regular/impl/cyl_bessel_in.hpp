//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/bessel/detail/kernel_bessel_i.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<callable_options O, typename I, typename T> constexpr
  EVE_FORCEINLINE as_wide_as_t<T, I>
  cyl_bessel_in_(EVE_REQUIRES(cpu_), O const&, I nu, T x)
{
    if constexpr( integral_value<I> )
    {
      if constexpr( simd_value<I> && scalar_value<T> )
      {
        using c_t = wide<T, cardinal_t<I>>;
        return cyl_bessel_in(convert(nu, as(x)), c_t(x));
      }
      else if constexpr( simd_value<I> && simd_value<T> )
      {
        using elt_t = element_type_t<T>;
        auto tnu    = convert(nu, as(elt_t()));
        return cyl_bessel_in(tnu, x);
      }
      else if constexpr( integral_scalar_value<I> )
      {
        return cyl_bessel_in(T(nu), x);
      }
    }
    else // I is floating
    {
      if constexpr( simd_value<I> && scalar_value<T> )
      {
        using c_t = wide<T, cardinal_t<I>>;
        return cyl_bessel_in(nu, c_t(x));
      }
      else if constexpr( scalar_value<I> && simd_value<T> )
      {
        return cyl_bessel_in(T(nu), x);
      }
      else
      {
        return kernel_bessel_i(nu, x);
      }
    }
  }
}
