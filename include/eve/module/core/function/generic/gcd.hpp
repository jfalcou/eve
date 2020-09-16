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

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/any.hpp>
#include <eve/function/if_else.hpp>

#include <type_traits>
//#include <eve/function/rem.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<integral_real_value T, integral_real_value U>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(gcd, a, b);
  }

  template<integral_real_value T> EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T a, T b) noexcept

  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( a < b )
          std::swap(a, b);
        while( b )
        {
          T r = a % b;
          a   = b;
          b   = r;
        }
        return a;
      }
      else
      {
        return map(gcd, a, b);
        //         auto test = is_nez(b);
        //         while (any(test))
        //         {
        //           auto r = if_else(test, rem(a, b), zero_); //TODO when rem at hand
        //           a = if_else(test, b, a);
        //           b = r;
        //           test = is_nez(b);
        //         }
        //         return a;
      }
    }
    else
      return apply_over(gcd, a, b);
  }

}

