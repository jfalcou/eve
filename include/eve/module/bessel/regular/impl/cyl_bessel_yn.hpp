//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <array>
#include <eve/module/real/special/detail/evaluate_rational.hpp>
#include <eve/module/real/special/detail/kernel_bessel_y.hpp>

namespace eve::detail
{
  // nu is floating
  //////////////////////////////////////////////////////////////////
  // floating scalar,  floating simd -> floating simd,  floating simd
  template<floating_real_scalar_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto cyl_bessel_yn_(EVE_SUPPORTS(cpu_), I nu, T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto flintx = is_flint(nu);
      return flintx ? kernel_bessel_y_int(nu, x) : kernel_bessel_y_flt(T(nu), x);
    }
    else return apply_over(cyl_bessel_yn, nu, x);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T cyl_bessel_yn_(EVE_SUPPORTS(cpu_), T nu, T x) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      auto flintx = is_flint(nu);
      return flintx ? kernel_bessel_y_int(nu, x) : kernel_bessel_y_flt(nu, x);
    }
    else //simd
    {
      if constexpr(has_native_abi_v<T>)
      {
        auto flint_nu = is_flint(nu);
        if (eve::all(flint_nu))  return kernel_bessel_y_int(nu, x);
        else if (eve::none(flint_nu)) return kernel_bessel_y_flt(nu, x);
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
  template<integral_simd_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE auto cyl_bessel_yn_(EVE_SUPPORTS(cpu_), I nu, T x) noexcept
  {
    using c_t = wide <T, cardinal_t<I>>;
    return cyl_bessel_yn(nu, c_t(x));
  }

  // scalar integral,  floating scalar
  template<integral_scalar_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE auto cyl_bessel_yn_(EVE_SUPPORTS(cpu_), I nu, T x) noexcept
  {
    return kernel_bessel_y_int(nu, x);
  }
  // scalar integral,  floating simd
  template<integral_scalar_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto cyl_bessel_yn_(EVE_SUPPORTS(cpu_), I nu, T x) noexcept
  {
    using i_t = wide <I, cardinal_t<T>>;
    return kernel_bessel_y_int(i_t(nu), x);
  }

  // integral simd,  floating scalar
  template<integral_simd_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto cyl_bessel_yn_(EVE_SUPPORTS(cpu_), I nu, T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto n = convert(nu, as<element_type_t<T>>());
      return kernel_bessel_y_int(n, x);
    }
    else return apply_over(cyl_bessel_yn, nu, x);
  }

}
