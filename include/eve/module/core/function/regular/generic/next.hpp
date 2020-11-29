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
#include <eve/function/converter.hpp>
#include <eve/function/inc.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        return bitfloating(inc(bitinteger(a)));
      }
      else if constexpr(integral_value<T>)
      {
        return inc(a);
      }
    }
    else
    {
      return apply_over(next, a);
    }
  }

  //////////////////////////////////////////////////////////////
  // two parameters
  //////////////////////////////////////////////////////////////
  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
    {
      if constexpr(floating_value<T>)
      {
        using i_t = as_integer_t<T>;
        return bitfloating(bitinteger(a)+to_<i_t>(n));
      }
      else if constexpr(integral_value<T>)
      {
        return to_<T>(a+to_<T>(n));
      }
    }
    else
    {
      return apply_over(next, a, n);
    }
  }
}
