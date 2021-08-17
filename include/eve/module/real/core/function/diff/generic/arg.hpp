//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/arg.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/zero.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T arg_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(is_gtz(n), zero, arg(x));
    }
    else
      return apply_over(diff_1st(arg), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T arg_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x) noexcept
  {
    return zero(as(x));
  }
}
