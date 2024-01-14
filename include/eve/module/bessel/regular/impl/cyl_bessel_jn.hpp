//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/bessel/detail/kernel_bessel_j.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/as_element.hpp>

namespace eve::detail
{
  template<typename I, typename T, callable_options O>
  EVE_FORCEINLINE as_wide_as_t<T, I>
  cyl_bessel_jn_(EVE_REQUIRES(cpu_), O const&, I nu, T x)
  {
    if constexpr(floating_value<I>)
    {
      if constexpr(scalar_value<I> && simd_value<T>)
      {
        if constexpr( has_native_abi_v<T> )
        {
          auto flintx = is_flint(nu);
          return flintx ? kernel_bessel_j_int(nu, x) : kernel_bessel_j_flt(T(nu), x);
        }
        else return apply_over(cyl_bessel_jn, nu, x);
      }
      else  if (std::same_as<T, I>)
      {
        if constexpr( scalar_value<T> )
        {
          auto flintx = is_flint(nu);
          return flintx ? kernel_bessel_j_int(nu, x) : kernel_bessel_j_flt(nu, x);
        }
        else // simd
        {
          if constexpr( has_native_abi_v<T> )
          {
            auto flint_nu = is_flint(nu);
            if( eve::all(flint_nu) ) return kernel_bessel_j_int(nu, x);
            else if( eve::none(flint_nu) ) return kernel_bessel_j_flt(nu, x);
            else
            {
              auto nu_int = if_else(flint_nu, nu, zero);
              auto nu_flt = if_else(flint_nu, T(0.5), nu);
              return if_else(flint_nu, kernel_bessel_j_int(nu_int, x), kernel_bessel_j_flt(nu_flt, x));
            }
          }
          else return apply_over(cyl_bessel_jn, nu, x);
        }
      }
    }
    else // nu is integral
    {
      if constexpr(simd_value<I> && scalar_value<T>)
      {
        using c_t = wide<T, cardinal_t<I>>;
        return cyl_bessel_jn(nu, c_t(x));
      }
      else if constexpr(scalar_value<I> && scalar_value<T>)
      {
        return kernel_bessel_j_int(nu, x);
      }
      else if constexpr(simd_value<T>)
      {
        if constexpr( has_native_abi_v<T> )
        {
          auto n = convert(nu, as_element(x));
          return kernel_bessel_j_int(n, x);
        }
        else return apply_over(cyl_bessel_jn, nu, x);
      }
    }
  }
}
