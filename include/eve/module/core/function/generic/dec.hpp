//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<real_value T>
  EVE_FORCEINLINE constexpr T dec_(EVE_SUPPORTS(cpu_)
                                  , T const &v) noexcept
  {
    if constexpr(has_native_abi_v<T>)  return v - One(as(v));
    else                     return apply_over(dec, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated case
  template<real_value T>
  EVE_FORCEINLINE constexpr T dec_(EVE_SUPPORTS(cpu_)
                                  , saturated_type const &
                                  , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
           if constexpr(integral_value<T>) return dec[ a != Valmin(as(a)) ](a);
      else if constexpr(floating_value<T>) return dec(a);
    }
    else return apply_over(saturated_(dec), a);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto dec_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::dec, t);
  }

  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto dec_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, saturated_(eve::dec), t);
  }
}
