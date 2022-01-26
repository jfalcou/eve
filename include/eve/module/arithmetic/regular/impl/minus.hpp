//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T minus_(EVE_SUPPORTS(cpu_), T v) noexcept
  {
          if constexpr(simd_value<T>)     return -v;
    else  if constexpr(floating_value<T>) return bit_xor(v, signmask(eve::as(v)));
    else                                  return T{0} - v;
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto minus_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op(  cond, eve::minus, t);
  }

  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto minus_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    auto substract =  [](auto x, auto y){return x-y;};
    return mask_op(  cond, substract, t, f);
  }
}
