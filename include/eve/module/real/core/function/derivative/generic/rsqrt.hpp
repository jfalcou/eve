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

#include <eve/function/derivative/rsqrt.hpp>
#include <eve/function/derivative/pow.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/mhalf.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T rsqrt_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return diff_1st(pow)(x, mhalf(as(x)), n);
    }
    else
      return apply_over(diff_1st(pow), x, mhalf(as(x)), n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T rsqrt_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return 3*mhalf(as(x))*rec(sqrt(x)*x);
    else
      return apply_over(diff_1st(rsqrt), x);

  }
}
