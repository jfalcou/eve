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

#include <eve/constant/half.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N, unsigned_value P>
  EVE_FORCEINLINE constexpr T average_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , T y
                                   , N n
                                   , P p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto np = n+p;
      return if_else(np == 0, average(x, y), if_else(np == 1,  half(as(x)), zero));
    }
    else
      return apply_over(derivative_1st(average), x, y, n, p);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T average_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x, T ) noexcept
  {
    return half(as(x));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T average_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<2> const &
                                    , T x, T ) noexcept
  {
    return half(as(x));
  }
}
