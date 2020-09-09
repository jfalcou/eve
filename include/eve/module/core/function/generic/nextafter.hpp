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
#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/regular.hpp>
#include <type_traits>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////
  // decorated calls
  template<real_value T, real_value U, decorator D>
  EVE_FORCEINLINE constexpr auto
  nextafter_(EVE_SUPPORTS(cpu_), D const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(D()(nextafter), a, b);
  }

  template<real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto
  nextafter_(EVE_SUPPORTS(cpu_), D const &, T const &a, T const &b) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      if constexpr( std::is_same_v<D, pedantic_type> )
      {
        if( is_unordered(a, b) )
          return Allbits(as(a));
      }

      return (a < b) ? next(a) : ((b < a) ? prev(a) : a);
    }
    else if constexpr( simd_value<T> )
    {
      auto tmp = if_else(a < b, next(a), if_else(b < a, prev(a), a));
      if constexpr( std::is_same_v<D, pedantic_type> )
      {
        return if_else(is_unordered(a, b), eve::allbits, tmp);
      }
      else
      {
        return tmp;
      }
    }
  }

  //////////////////////////////////////////////////////////////
  // regular call
  template<real_value T, real_value U>
  EVE_FORCEINLINE constexpr auto nextafter_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return nextafter(regular_type(), a, b);
  }
}

