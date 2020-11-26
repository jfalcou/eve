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

#include <eve/detail/implementation.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/shr.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto average_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(average, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE  T average_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  requires has_native_abi_v<T>
  {
    if constexpr(integral_value<T>) return (a & b) + ((a ^ b) >> 1);
    else                            return fma(a, half(eve::as(a)),b*half(eve::as(a)));
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto average_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::average, t, f);
  }

}
