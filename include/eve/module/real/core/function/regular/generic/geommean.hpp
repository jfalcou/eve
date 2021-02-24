//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE  auto geommean_(EVE_SUPPORTS(cpu_)
                            , T a
                            , U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(geommean, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE  T geommean_(EVE_SUPPORTS(cpu_)
                            , T a
                            , T b) noexcept
  requires has_native_abi_v<T>
  {
    return if_else(is_nltz(a) || is_nltz(b), sqrt(a)*sqrt(b), allbits);
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto geommean_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::geommean, t, f);
  }

}
