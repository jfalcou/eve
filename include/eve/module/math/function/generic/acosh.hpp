//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE

   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_MATH_FUNCTION_GENERIC_ACOSH_HPP_INCLUDED
#define EVE_MODULE_MATH_FUNCTION_GENERIC_ACOSH_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/sqrt.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acosh_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      T          t    = dec(x);
      auto const test = is_greater(t, Oneotwoeps<T>());

      if constexpr( simd_value<T> )
      {
        T z = if_else(test, x, t + sqrt(t + t + sqr(t)));
        return add[test](log1p(z), Log_2<T>());
      }
      else if constexpr( scalar_value<T> )
      {
        if( test )
        {
          return eve::log(t) + Log_2<T>();
        }
        else
        {
          return eve::log1p(t + eve::sqrt(t + t + sqr(t)));
        }
      }
    }
    else
    {
      return apply_over(acosh, x);
    }
  }
}

#endif
