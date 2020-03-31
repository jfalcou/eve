//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_SKELETON_CALLS_HPP_INCLUDED
#define EVE_DETAIL_SKELETON_CALLS_HPP_INCLUDED

#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/cardinal.hpp>


namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // binary arithmetic operators scheme
  template<typename Obj, real_value T, real_value U>
  EVE_FORCEINLINE  auto arithmetic_call(Obj op
                                       , T const &a
                                       , U const &b) noexcept
  requires compatible_values<T, U>
  {
    if constexpr(scalar_value<T> && scalar_value<U>)    //both are scalar so of the same type
    {
      return op(a, b); 
    }
    else if constexpr(scalar_value<T> != scalar_value<U>) //  one is scalar and one simd
    {                                                     // no one is_native to avoid an early splat 
      if constexpr(!(native<T> && native<U>)) return apply_over(op, a, b); 
      else if constexpr(scalar_value<T>)           return op(U(a), b);
      else if constexpr(scalar_value<U>)           return op(a, T(b)); 
    }
    else if constexpr(simd_value<T> && simd_value<U>) // both are simd so of the same type
    {
      if constexpr(native<T> && native<U>) return op(a, b); // generally already taken by arch specific intrisicss
      else                                 return apply_over(op, a, b); 
    }
  } 
}

#endif
