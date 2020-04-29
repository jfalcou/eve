//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_LERP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_LERP_HPP_INCLUDED

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
  EVE_FORCEINLINE auto lerp_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &t) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(lerp, a, b, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T lerp_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &t) noexcept
  {
    return fma(t, b - a, a);
  }

  ////////////////////////////////////////////////////////////////////////////
  // pedantic/numeric/raw
  template<floating_real_value T, floating_real_value U, floating_real_value V, decorator D>
  EVE_FORCEINLINE auto
  lerp_(EVE_SUPPORTS(cpu_), D const &, T const &a, U const &b, V const &t) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(D()(lerp), a, b, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T
  lerp_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a, T const &b, T const &t) noexcept
      requires has_native_abi_v<T>
  {
    return fma(t, b - a, a);
  }

  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE T
  lerp_(EVE_SUPPORTS(cpu_), D const &, T const &a, T const &b, T const &t) noexcept
      requires has_native_abi_v<T>
  {
    return D()(fma)(t, b - a, a);
  }
}

#endif
