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
  template<typename I, typename T, callable_options O> constexpr
  EVE_FORCEINLINE as_wide_as_t<T, I>
  cyl_bessel_jn_(EVE_REQUIRES(cpu_), O const&, I nu, T x)
  {
    using w_t = as_wide_as_t<T, I>;
    if constexpr(floating_value<I>)
    {
      if constexpr(scalar_value<I> && simd_value<T>)
      {
        auto flintx = is_flint(nu);
        return flintx ? kernel_bessel_j_int(nu, x) : kernel_bessel_j_flt(T(nu), x);
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
          auto flint_nu = is_flint(nu);
          if( eve::all(flint_nu) )        return kernel_bessel_j_int(nu, x);
          else if( eve::none(flint_nu) )  return kernel_bessel_j_flt(nu, x);
          else
          {
            auto nu_int = if_else(flint_nu, nu, zero);
            auto nu_flt = if_else(flint_nu, T(0.5), nu);
            return if_else(flint_nu, kernel_bessel_j_int(nu_int, x), kernel_bessel_j_flt(nu_flt, x));
          }
        }
      }
    }
    else // nu is integral
    {
      if      constexpr(simd_value<I> && scalar_value<T>)   return cyl_bessel_jn(nu, w_t(x));
      else if constexpr(scalar_value<I> && scalar_value<T>) return kernel_bessel_j_int(nu, x);
      else if constexpr(simd_value<T>)                      return kernel_bessel_j_int(convert(nu, as_element(x)), x);
    }
  }
}
