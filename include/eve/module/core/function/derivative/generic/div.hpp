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

#include <eve/constant/one.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/derivative/rec.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N, unsigned_value P>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , T y
                                   , N n
                                   , P p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto dy = derivative(rec)(y, p);
      auto res = if_else(n > 1,  zero,
                         if_else(n == 0, dy*x, dy));
      return res;
    }
    else
      return apply_over(derivative1(div), x, y, n, p);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T , T y ) noexcept
  {

    return rec(y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<2> const &
                                    , T x, T y ) noexcept
  {

    return -rec(y*y)*x;
  }
}
