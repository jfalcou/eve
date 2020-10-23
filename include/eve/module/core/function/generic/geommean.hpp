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
#include <eve/detail/function/conditional.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
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

  template<floating_real_value T>
  EVE_FORCEINLINE  T geommean_(EVE_SUPPORTS(cpu_)
                           ,  pedantic_type const&
                            , T a
                            , T b) noexcept
  requires has_native_abi_v<T>
  {
    auto m = max(a, b);
    auto im = if_else(is_nez(m), rec(m), m);
    auto z = min(a, b)*im;
    return if_else(is_nltz(a) || is_nltz(b), sqrt(z)*m, allbits);
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
