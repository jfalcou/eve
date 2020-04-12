//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_ORNOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_ORNOT_HPP_INCLUDED

#include <eve/forward.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/if_else.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto bit_ornot_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , U const &b) noexcept
  requires bit_compatible_values<T,U>
  {
    return bit_call(bit_ornot, a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto bit_ornot_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b) noexcept
  {
    if constexpr(floating_value<T>)
    {
      using b_t = as_integer_t<T, unsigned>;
      return bit_cast( b_t(bit_cast(a,as<b_t>()) | ~bit_cast(b,as<b_t>())), as(a) );
    }
    else return T(a | ~b);
  }

  template<real_simd_value T>
  EVE_FORCEINLINE auto bit_ornot_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b) noexcept
  {
    return bit_or(a, bit_not(b)); // fallback never taken if proper intrinsics are at hand
  }


  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto bit_ornot_(EVE_SUPPORTS(cpu_)
                           , T const & cond
                           , U const & t
                           , V const & f) noexcept
  requires bit_compatible_values<U, V>
  {
    using r_t = decltype(bit_ornot(t, f));
         if constexpr(scalar_value<T>) return  cond ? bit_ornot(t, f) : r_t(t);
    else if constexpr(simd_value<T>)   return  if_else(cond,bit_ornot(t, f), t);
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto bit_ornot_(EVE_SUPPORTS(cpu_)
                           , not_t<T> const & cond
                           , U const & t
                           , V const & f) noexcept
  requires bit_compatible_values<U, V>
  {
    using r_t = decltype(bit_ornot(t, f));
         if constexpr(scalar_value<T>) return  cond.value ? r_t(t) : bit_ornot(t, f);
    else if constexpr(simd_value<T>)   return  if_else(cond.value,t, bit_ornot(t, f));
  }
}

#endif
