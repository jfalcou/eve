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
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/raw.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto lerp_(EVE_SUPPORTS(cpu_)
                            , T const &a, U const &b, V const &t) noexcept
  requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(lerp, a, b, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T lerp_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &t) noexcept
  {
    return fma(t, b, fnma(t, a, a));
  }

  template<floating_real_value T, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto lerp_(EVE_SUPPORTS(cpu_), raw_type const &
                            , T const &a, U const &b, V const &t) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(raw(lerp), a, b, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T
  lerp_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a, T const &b, T const &t) noexcept
      requires has_native_abi_v<T>
  {
    return fma(t, b, fnma(t, a, a));
    ;
  }
}
