//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/if_else.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>

namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto bit_or_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires bit_compatible_values<U, V>
  {
    return mask_op(  cond, eve::bit_or, t, f);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  auto bit_or_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
    requires bit_compatible_values<T0, T1> && (bit_compatible_values<T1, Ts> && ...)
  {
    auto that = bit_or(a0,a1);
    ((that = bit_or(that, args)),...);
    return that;
  }

  template<conditional_expr C, real_value T0, real_value T1, real_value ...Ts>
  auto bit_or_(EVE_SUPPORTS(cpu_), C const &cond, T0 a0, T1 a1, Ts... args)
    requires bit_compatible_values<T0, T1> && (bit_compatible_values<T1, Ts> && ...)
  {
    auto that = bit_or(a1,args...);
    return mask_op( cond, eve::bit_or, a0, that);

  }
}
