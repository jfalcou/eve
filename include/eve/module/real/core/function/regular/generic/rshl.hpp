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
#include <eve/function/if_else.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/max.hpp>
#include <eve/function/shr.hpp>
#include <eve/constant/zero.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<integral_value T, integral_value U>
  EVE_FORCEINLINE  auto rshl_(EVE_SUPPORTS(cpu_)
                            , T const &a0
                            , U const &a1) noexcept
  {
    if constexpr(unsigned_value<U>)
    {
      return T(a0 << a1);
    }
    else if constexpr(scalar_value<U>)
    {
      return (a1 > 0) ? T(a0 << a1) : T(a0 >> -a1);
    }
    else
    {
      if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
      {
#ifndef NDEBUG
      return if_else(is_gtz(a1), T(a0 << max(zero(eve::as(a1)), a1)), T(a0 >> max(zero(eve::as(a1)), -a1)));
#else
      return if_else(is_gtz(a1), T(a0 << a1), T(a0>> -a1));
#endif
      }
      else
      {
        return apply_over(rshl, a0, a1);
      }
    }
  }
}
