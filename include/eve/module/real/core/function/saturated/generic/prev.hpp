//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/next.hpp>
#include <eve/function/saturated/sub.hpp>
#include <eve/function/saturated/dec.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const &
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto z =  prev(a);
        if constexpr(eve::platform::supports_nans) return if_else(is_nan(a), eve::allbits, z);
        else                                       return z;
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(dec)(a);
      }
    }
    else  { return apply_over(saturated(prev), a);    }
  }

  //////////////////////////////////////////////////////////////
  // two parameters
  //////////////////////////////////////////////////////////////
  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const &
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto z =  prev(a, n);
        if constexpr(eve::platform::supports_nans) return if_else(is_nan(a), eve::allbits, z);
        else                                       return z;
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(sub)(a, to_<T>(n));
      }
    }
    else  { return apply_over(saturated(prev), a, n);    }
  }
}
