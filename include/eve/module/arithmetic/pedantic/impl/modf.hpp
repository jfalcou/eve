//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/trunc.hpp>
#include <eve/detail/kumi.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr kumi::tuple<T, T>
  modf_(EVE_SUPPORTS(cpu_), pedantic_type const &, T a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( floating_real_value<T> )
      {
        if constexpr( scalar_value<T> )
        {
          if( is_infinite(a) )
            return {zero(eve::as(a)), a};
          auto t = trunc(a);
          return {a - t, t};
        }
        else
        {
          auto t = trunc(a);
          auto f = if_else(is_infinite(a), eve::zero, a - t);
          return {f, t};
        }
      }
      else
      {
        return {zero(eve::as(a)), a};
      }
    }
    else
    {
      return apply_over2(pedantic(modf), a);
    }
  }
}
