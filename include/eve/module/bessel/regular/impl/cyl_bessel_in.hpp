//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/ieee.hpp>
#include <eve/module/math.hpp>
#include <eve/module/bessel/detail/kernel_bessel_i.hpp>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////////
  // floating scalar,  floating simd -> floating simd,  floating simd
  template<floating_real_value T>
  EVE_FORCEINLINE auto cyl_bessel_in_(EVE_SUPPORTS(cpu_), T nu, T x) noexcept
  requires has_native_abi_v<T>
  {
    return kernel_bessel_i(nu, x);
  }

  template<value I, floating_real_value T>
  EVE_FORCEINLINE auto cyl_bessel_in_(EVE_SUPPORTS(cpu_), I nu, T x) noexcept
  {
    if constexpr(has_native_abi_v<T> && has_native_abi_v<I>)
    {
      if constexpr(integral_value<I>)
      {
        if constexpr(simd_value<I> && scalar_value<T>)
        {
          using c_t = wide <T, cardinal_t<I>>;
          return cyl_bessel_in(convert(nu, as(x)), c_t(x));
        }
        else if constexpr(simd_value<I> && simd_value<T>)
        {
          using elt_t = element_type_t<T>;
          auto tnu = convert(nu, as(elt_t()));
          return cyl_bessel_in(tnu, x);
        }
        else if constexpr(integral_scalar_value<I>)
        {
          return cyl_bessel_in(T(nu), x);
        }
      }
      else
      {
        if constexpr(simd_value<I> && scalar_value<T>)
        {
          using c_t = wide <T, cardinal_t<I>>;
          return cyl_bessel_in(nu, c_t(x));
        }
        else if constexpr(scalar_value<I> && simd_value<T>)
        {
          return cyl_bessel_in(T(nu), x);
        }
      }
    }
    else return apply_over(cyl_bessel_in, nu, x);
  }
}
