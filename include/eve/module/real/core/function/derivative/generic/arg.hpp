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

#include <eve/function/arg.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/zero.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T arg_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(is_gtz(n), zero, arg(x));
    }
    else
      return apply_over(derivative_1st(arg), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T arg_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x) noexcept
  {
    return zero(as(x));
  }
}
