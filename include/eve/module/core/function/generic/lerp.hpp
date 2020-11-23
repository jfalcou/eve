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
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/raw.hpp>

#include <type_traits>


// TODO revision to:
// pedantic will call pedantic fma and fnma
// and the no extrapolation will be obtained through named parameter no_extrap = t

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto lerp_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &t) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(lerp, a, b, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T lerp_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &t) noexcept
  {
    if constexpr(has_native_abi_v<T>) return fma(t, b, fnma(t, a, a));
    else return apply_over(lerp, a, b, t);
  }

  ////////////////////////////////////////////////////////////////////////////
  // pedantic/numeric
  template<floating_real_value T, floating_real_value U, floating_real_value V, decorator D>
  EVE_FORCEINLINE auto
  lerp_(EVE_SUPPORTS(cpu_), D const &, T const &a, U const &b, V const &t) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(D()(lerp), a, b, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T
  lerp_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, T const &b, T const &t) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto test = is_gez(t) && (t <= one(as(t)));
      return if_else(test, lerp(a, b, t), allbits);
    }
    else return apply_over(pedantic(lerp), a, b, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T
  lerp_(EVE_SUPPORTS(cpu_), numeric_type const &, T const &a, T const &b, T const &t) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto test = a == b;
      return if_else(test, a, lerp(a, b, t));
    }
    else return apply_over(numeric(lerp), a, b, t);
  }
}
