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

#include <eve/function/pow.hpp>

#include <eve/function/dec.hpp>
#include <eve/function/log.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/log_2.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x, T y, N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return pow(x, y)*pow(-log_2(as(x)), n);
    }
    else
      return apply_over(derivative(pow), x, y, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow(x, dec(y))*y;
  }

   template<floating_real_value T>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow(x, y)*log(x);
  }
}
