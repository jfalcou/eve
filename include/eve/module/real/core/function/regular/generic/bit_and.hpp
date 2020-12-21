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

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/function/if_else.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto bit_and_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires bit_compatible_values<U, V>
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::bit_and, t, f);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  auto bit_and_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
    requires bit_compatible_values<T0, T1> && (bit_compatible_values<T1, Ts> && ...)
  {
    auto that = bit_and(a0,a1);
    ((that = bit_and(that, args)),...);
    return that;
  }
}
