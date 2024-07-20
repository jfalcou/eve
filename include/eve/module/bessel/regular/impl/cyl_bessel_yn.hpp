//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/bessel/detail/kernel_bessel_y.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/as_element.hpp>

namespace eve::detail
{
  // nu is floating
  //////////////////////////////////////////////////////////////////
  // floating scalar,  floating simd -> floating simd,  floating simd
  template<floating_value I, floating_value T, callable_options O> constexpr
  EVE_FORCEINLINE auto
  cyl_bessel_yn_(EVE_REQUIRES(cpu_), O const&, I nu, T x) noexcept
  requires(scalar_value<I> && simd_value<T>)
  {
    auto flintx = is_flint(nu);
    return flintx ? kernel_bessel_y_int(nu, x) : kernel_bessel_y_flt(T(nu), x);
  }

  template<floating_value T, callable_options O> constexpr
  EVE_FORCEINLINE T
  cyl_bessel_yn_(EVE_REQUIRES(cpu_), O const&, T nu, T x) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      auto flintx = is_flint(nu);
      return flintx ? kernel_bessel_y_int(nu, x) : kernel_bessel_y_flt(nu, x);
    }
    else // simd
    {
      auto flint_nu = is_flint(nu);
      if( eve::all(flint_nu) ) return kernel_bessel_y_int(nu, x);
      else if( eve::none(flint_nu) ) return kernel_bessel_y_flt(nu, x);
      else
      {
        auto nu_int = if_else(flint_nu, nu, zero);
        auto nu_flt = if_else(flint_nu, T(0.5), nu);
        return if_else(flint_nu, kernel_bessel_y_int(nu_int, x), kernel_bessel_y_flt(nu_flt, x));
      }
    }
  }

  // nu is integral
  //////////////////////////////////////////////////////////////////
  // integral simd,  floating scalar -> integral simd, floating simd
  template<integral_value I, floating_value T, callable_options O> constexpr
  EVE_FORCEINLINE auto
  cyl_bessel_yn_(EVE_REQUIRES(cpu_), O const&, I nu, T x) noexcept
  {
    if constexpr(simd_value<I> && scalar_value<T>)
    {
      using c_t = wide<T, cardinal_t<I>>;
      return cyl_bessel_yn(nu, c_t(x));
    }
    else if constexpr(scalar_value<I> && simd_value<T>)
    {
      using i_t = wide<I, cardinal_t<T>>;
      return kernel_bessel_y_int(i_t(nu), x);
    }
    else if constexpr(simd_value<I> && simd_value<T>)
    {
      auto n = convert(nu, as_element(x));
      return kernel_bessel_y_int(n, x);
    }
    else return kernel_bessel_y_int(T(nu), x);
  }
}
