//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/bessel/detail/kernel_bessel_y.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <array>

namespace eve::detail
{
// nu is floating
//////////////////////////////////////////////////////////////////
// floating scalar,  floating simd -> floating simd,  floating simd
template<floating_ordered_value I, floating_ordered_value T>
EVE_FORCEINLINE auto
cyl_bessel_yn_(EVE_SUPPORTS(cpu_), I nu, T x) noexcept
requires(scalar_value<I> && simd_value<T>)
{
  if constexpr( has_native_abi_v<T> )
  {
    auto flintx = is_flint(nu);
    return flintx ? kernel_bessel_y_int(nu, x) : kernel_bessel_y_flt(T(nu), x);
  }
  else return apply_over(cyl_bessel_yn, nu, x);
}

template<floating_ordered_value T>
EVE_FORCEINLINE T
cyl_bessel_yn_(EVE_SUPPORTS(cpu_), T nu, T x) noexcept
{
  if constexpr( scalar_value<T> )
  {
    auto flintx = is_flint(nu);
    return flintx ? kernel_bessel_y_int(nu, x) : kernel_bessel_y_flt(nu, x);
  }
  else // simd
  {
    if constexpr( has_native_abi_v<T> )
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
    else return apply_over(cyl_bessel_yn, nu, x);
  }
}

// nu is integral
//////////////////////////////////////////////////////////////////
// integral simd,  floating scalar -> integral simd, floating simd
template<integral_value I, floating_ordered_value T>
EVE_FORCEINLINE auto
cyl_bessel_yn_(EVE_SUPPORTS(cpu_), I nu, T x) noexcept
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
    if constexpr( has_native_abi_v<T> )
    {
      auto n = convert(nu, as<element_type_t<T>>());
      return kernel_bessel_y_int(n, x);
    }
    else return apply_over(cyl_bessel_yn, nu, x);
  }
  else
    return kernel_bessel_y_int(T(nu), x);
}

}
