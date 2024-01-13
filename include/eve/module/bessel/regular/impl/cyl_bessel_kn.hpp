//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/bessel/detail/kernel_bessel_k.hpp>
#include <eve/as_element.hpp>

namespace eve::detail
{

  template<floating_ordered_value I, floating_ordered_value T, callable_options O>
  as_wide_as_t<T, I>
  cyl_bessel_kn_(EVE_REQUIRES(cpu_), O const&, I nu, T x)
  requires(scalar_value<I> && simd_value<T>)
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto flintx = is_flint(nu);
      return flintx ? kernel_bessel_k_int(nu, x) : kernel_bessel_k_flt(T(nu), x);
    }
    else return apply_over(cyl_bessel_kn, nu, x);
  }

  template<floating_ordered_value T, callable_options O>
  T  cyl_bessel_kn_(EVE_REQUIRES(cpu_), O const&, T nu, T x)
  {
    if constexpr( scalar_value<T> )
    {
      auto flintx = is_flint(nu);
      return flintx ? kernel_bessel_k_int(nu, x) : kernel_bessel_k_flt(nu, x);
    }
    else // simd
    {
      if constexpr( has_native_abi_v<T> )
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
      else return apply_over(cyl_bessel_kn, nu, x);
    }
  }

  template<integral_value I, floating_ordered_value T, callable_options O>
  as_wide_as_t<T, I>
  cyl_bessel_kn_(EVE_REQUIRES(cpu_), O const&, I nu, T x)
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
      if constexpr( has_native_abi_v<T> )
      {
        auto n = convert(nu, as_element(x));
        return kernel_bessel_k_int(n, x);
      }
      else return apply_over(cyl_bessel_kn, nu, x);
    }
  }
}
