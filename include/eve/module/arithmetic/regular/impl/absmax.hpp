//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_greater_equal.hpp>
#include <eve/function/max.hpp>
#include <eve/traits/common_compatible.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto absmax_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(absmax, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto absmax_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  requires has_native_abi_v<T>
  {
    return  eve::abs(eve::max(a, b));
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<decorator D, conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto absmax_(EVE_SUPPORTS(cpu_), C const &cond, D const &
                              , U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, D()(eve::absmax), t, f);
  }

  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto absmax_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::absmax, t, f);
  }


  //================================================================================================
  // N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1,Ts...> absmax_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    return eve::abs(eve::max(a0, a1, args...));
  }
}
