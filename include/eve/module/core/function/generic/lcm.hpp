//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_LCM_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_LCM_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/gcd.hpp>
#include <eve/function/if_else.hpp>

#include <type_traits>
//#include <eve/function/rem.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<integral_real_value T, integral_real_value U>
  EVE_FORCEINLINE auto lcm_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(lcm, a, b);
  }

  template<integral_real_value T> EVE_FORCEINLINE T lcm_(EVE_SUPPORTS(cpu_), T a, T b) noexcept

  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( !b || !a )
          return T(0);
        return abs(b / gcd(a, b) * a);
      }
      else
      {
        return abs(a * (b / gcd(a, if_else(b, b, eve::one_))));
      }
    }
    else
      return apply_over(lcm, a, b);
  }

}

#endif
