//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/saturated.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/detail/next_kernel.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/saturated/add.hpp>
#include <eve/module/core/saturated/inc.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template< real_value T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const &
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto z =  next(a);
        if constexpr(eve::platform::supports_nans) return if_else(is_nan(a), eve::allbits, z);
        else                                       return z;
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(inc)(a);
      }
    }
    else
    {
      return apply_over(saturated(next), a);
    }
  }

  //////////////////////////////////////////////////////////////
  // two parameters
  //////////////////////////////////////////////////////////////
  template<real_value T, integral_value U>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const &
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
    {
      if constexpr(floating_value<T>)
      {
        auto z =  next(a, n);
        if constexpr(eve::platform::supports_nans) return if_else(is_nan(a), eve::allbits, z);
        else                                       return z;
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(add)(a, to_<T>(n));
      }
    }
    else
    {
      return apply_over(saturated(next), a, n);
    }
  }
}
