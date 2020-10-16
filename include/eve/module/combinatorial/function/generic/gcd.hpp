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
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/allbits.hpp>

#include <type_traits>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<value T, value U>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(gcd, a, b);
  }

  template<value T> EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  requires(has_native_abi_v<T>)
  {
    if constexpr( has_native_abi_v<T> )
    {
      std::cout << "native" << std::endl;
      auto valid = true_(as(a));
      if constexpr( signed_value<T> )
      {
        a = abs(a);
        b = abs(b);
      }
      if constexpr( floating_value<T> )
      {
        valid = is_flint(a) && is_flint(b);
        a = if_else(valid, a, zero);
        b = if_else(valid, b, zero);
      }
      a = if_else(is_eqz(a), b, a);
      b = if_else(is_eqz(b), a, b);
      T r;
      if constexpr( scalar_value<T> )
      {
        while( b )
        {
          if constexpr(integral_value<T>) r = a % b;
          else r = rem(a, b);
          a   = b;
          b   = r;
        }
        if constexpr(integral_value<T>) return a;
        else return  valid ? a: eve::allbits(as(a));
      }
      else
      {
        auto test = is_nez(b);
        T r(0);
        while (any(test))
        {
          if constexpr(integral_value<T>)
          {
            std::cout << "avant a " << a << std::endl;
            std::cout << "avant b " << b << std::endl;
            std::cout << "avant r " << r << std::endl;
              r = a % b;
            std::cout << "apres a " << a << std::endl;
            std::cout << "apres b " << b << std::endl;
            std::cout << "apres r " << r << std::endl;
          }

          else r = rem(a, b);
          a = if_else(test, b, a);
          b = r;
          test = is_nez(b);
        }
        if constexpr( floating_value<T> )
        {
          return if_else(valid, a, allbits);
        }
        else
        {
          return a;
        }

      }
    }
    else
    {
      std::cout << "not native" << std::endl;
      return apply_over(gcd, a, b);
    }

  }

}
