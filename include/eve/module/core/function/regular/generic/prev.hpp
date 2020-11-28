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
#include <eve/module/core/detail/generic/next_kernel.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/next.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        return bitfloating(dec(bitinteger(a)));
      }
      else if constexpr(integral_value<T>)
      {
        return dec(a);
      }
    }
    else
    {
      return apply_over(prev, a);
    }
  }

  //////////////////////////////////////////////////////////////
  // two parameters
  //////////////////////////////////////////////////////////////
  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        using i_t = as_integer_t<T>;
        return bitfloating(bitinteger(a)-to_<i_t>(n));
      }
      else if constexpr(integral_value<T>)
      {
        return a-to_<T>(n);
      }
    }
    else  { return apply_over(prev, a, n);    }
  }
}
