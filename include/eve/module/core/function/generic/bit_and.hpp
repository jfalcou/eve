//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_AND_HPP_INCLUDED

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/if_else.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto bit_and_(EVE_SUPPORTS(cpu_)
                           , T const & cond
                           , U const & t
                           , V const & f) noexcept
  requires bit_compatible_values<U, V>
  {
    using r_t = decltype(bit_and(t, f));
         if constexpr(scalar_value<T>) return cond ? bit_and(t, f) : r_t(t);
    else if constexpr(simd_value<T>)   return if_else(cond,bit_and(t, f), t);
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto bit_and_(EVE_SUPPORTS(cpu_)
                           , not_t<T> const & cond
                           , U const & t
                           , V const & f) noexcept
  requires bit_compatible_values<U, V>
  {
    using r_t = decltype(bit_and(t, f));
         if constexpr(scalar_value<T>) return cond.value ? r_t(t) : bit_and(t, f);
    else if constexpr(simd_value<T>)   return if_else(cond.value,t, bit_and(t, f));
  }
}

#endif
