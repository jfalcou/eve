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

#include <eve/function/sqr.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T sqr_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(is_eqz(n), sqr(x),
                     if_else(is_equal(n, one(as(n))), x+x,
                             if_else(is_equal(n, N(2)), T(2), zero)));
    }
    else
      return apply_over(derivative1(sqr), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sqr_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x) noexcept
  {

    return x+x;
  }
}
