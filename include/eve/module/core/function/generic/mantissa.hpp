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

#include <eve/detail/implementation.hpp>
#include <eve/platform.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/constant/mantissamask.hpp>
#include <eve/constant/one.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>


namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T mantissa_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if(!a) return a;
        if constexpr(eve::platform::supports_invalids)
        {
          if(is_not_finite(a)) return a;
        }
        return bit_or(bit_and(a, Mantissamask<T>()),One(as(a)));
      }
      else if constexpr(simd_value<T>)
      {
        auto test =  is_eqz(a);
        if constexpr(eve::platform::supports_invalids)
        {
          test =  test || is_not_finite(a);
        }
        return if_else(test, a, bit_or(bit_and(a,Mantissamask<T>()),One<T>()));
      }
    }
    else return apply_over(mantissa, a);
  }
}

