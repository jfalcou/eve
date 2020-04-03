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

#include <eve/forward.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/if_else.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto bit_and_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , U const &b) noexcept
  requires bit_compatible_values<T,U>
  {
    return bit_call(bit_and, a, b); 
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto bit_and_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b) noexcept
  {
    if constexpr(floating_value<T>)
    {
      using b_t = as_integer_t<T, unsigned>;
      return bit_cast( b_t(bit_cast(a,as<b_t>()) & bit_cast(b,as<b_t>())), as(a) );
    }
    else return T(a & b);
  }
  
  template<real_simd_value T>
  EVE_FORCEINLINE auto bit_and_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b) noexcept
  {
    return apply_over(bit_and, a, b); // fallback never taken if proper intrinsics are at hand
  }

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

namespace eve
{
  template<value T, value U>
  EVE_FORCEINLINE auto operator&( T const &a
                                , U const &b) noexcept
  -> decltype( eve::bit_and(a,b) )
  {
    return eve::bit_and(a, b);
  }
}

#endif
