//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/fma.hpp>
#include <eve/concept/properly_convertible.hpp>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto fma_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept
  requires properly_convertible<U, V, T>
  {
    using r_t =  common_compatible_t<T, U, V>;
    return arithmetic_call(fma, r_t(a), r_t(b), r_t(c));
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE T fma_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &c) noexcept
  {
    return a * b + c;
  }

  template<real_simd_value T>
  EVE_FORCEINLINE T fma_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &c) noexcept
  requires has_native_abi_v<T>
  {
    return a * b + c; // fallback never taken if proper intrinsics are at hand
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto fma_(EVE_SUPPORTS(cpu_), C const &cond, T const &a, U const &b, V const &c) noexcept
  requires properly_convertible<U, V, T>
  {
    using r_t =  common_compatible_t<T, U, V>;
    return mask_op(  cond, eve::fma, r_t(a), r_t(b), r_t(c));
  }

}
