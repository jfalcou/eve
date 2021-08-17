//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/max.hpp>
#include <eve/function/saturated.hpp>

#include <concepts>

namespace eve::detail
{

  template<real_value T>
  EVE_FORCEINLINE constexpr T abs_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( signed_integral_scalar_value<T> )
      {
        return ((a == valmin(eve::as(a))) ? valmax(eve::as(a)) : eve::abs(a));
      }
      else if constexpr( signed_integral_simd_value<T> )
      {
        return if_else(a == valmin(eve::as(a)), valmax(eve::as(a)), eve::abs(a));
      }
      else if constexpr( floating_value<T> || unsigned_value<T> )
      {
        return eve::abs(a);
      }
    }
    else
    {
      return apply_over(saturated(abs), a);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case

  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto abs_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &, U const &t) noexcept
  {
    return mask_op( cond, saturated(eve::abs), t);
  }
}
