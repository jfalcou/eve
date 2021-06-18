//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/pedantic.hpp>
#include <type_traits>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////
  // decorated calls
  template<real_value T, real_value U>
  EVE_FORCEINLINE constexpr auto
  nextafter_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(nextafter), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr auto
  nextafter_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, T const &b) noexcept
  requires has_native_abi_v<T>
  {
    if constexpr( scalar_value<T> )
    {
         if( is_unordered(a, b) ) return allbits(eve::as(a));
         return (a < b) ? next(a) : ((b < a) ? prev(a) : a);
    }
    else if constexpr( simd_value<T> )
    {
      return if_else( is_unordered(a, b), allbits, if_else(a < b, next(a), if_else(b < a, prev(a), a)));
    }
  }
}
