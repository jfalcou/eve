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

#include <eve/function/sub.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N, unsigned_value P>
  EVE_FORCEINLINE constexpr T sub_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , T y
                                   , N n
                                   , P p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto np = n+p;
      return if_else(np == 0, x-y, if_else(n+p == 1, if_else(n == 1, one(as(x)), mone), zero));
    }
    else
      return apply_over(derivative_1st(sub), x, y, n, p);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sub_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x, T ) noexcept
  {

    return one(as(x));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sub_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<2> const &
                                    , T x, T ) noexcept
  {

    return mone(as(x));
  }
}
