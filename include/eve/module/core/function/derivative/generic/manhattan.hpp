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
#include <eve/function/sign.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/derivative/sub.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/sign.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N, unsigned_value P>
  EVE_FORCEINLINE constexpr T manhattan_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , T y
                                   , N n
                                   , P p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(n+p == 0, manhattan(x, y),
                     if_else(n+p == 1,
                             if_else(p == 1, sign(y), sign(x)),
                             zero
                            )
                    );

    }
    else
      return apply_over(derivative_1st(manhattan), x, y, n, p);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T manhattan_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x, T ) noexcept
  {

    return sign(x);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T manhattan_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<2> const &
                                    , T , T y) noexcept
  {

    return sign(y);
  }
}
