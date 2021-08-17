//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/saturated/sub.hpp>
#include <eve/function/bit_xor.hpp>
#include <type_traits>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T minus_(EVE_SUPPORTS(cpu_), saturated_type const &, T v) noexcept
  {
    if constexpr(floating_value<T>) return bit_xor(v, signmask(eve::as(v)));
    else return if_else(v == valmin(as<T>()), valmax(as<T>()), minus(v));
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto minus_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &
                             , U const &t) noexcept
  {
    return mask_op(  cond, saturated(eve::minus), t);
  }

  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto minus_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &
                             , U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    auto substract =  [](auto x, auto y){return saturated(sub)(x, y);};
    return mask_op(  cond, substract(t, f), t);
  }
}
