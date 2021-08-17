//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/exp2.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/log_2.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T exp2_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return exp2(x)*pow(log_2(as(x)), n);
    }
    else
      return apply_over(diff_1st(exp2), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T exp2_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x) noexcept
  {
    return exp2(x)*log_2(as(x));
  }
}
