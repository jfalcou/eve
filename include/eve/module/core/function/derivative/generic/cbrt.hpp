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

#include <eve/function/derivative/pow.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/mhalf.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T cbrt_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(n == 0, cbrt(x), derivative2(pow)(x,T(1.0/3.0), n));
    }
    else
      return apply_over(derivative1(cbrt), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T cbrt_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x) noexcept
  {

    return rec(3*sqr(cbrt(x)));
  }
}
