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

#include <eve/function/is_equal.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T plus_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(is_eqz(n), x, if_else(is_equal(n, one(as(n))), one(as(x)), zero));
    }
    else
      return apply_over(derivative_1st(plus), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T plus_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x) noexcept
  {

    return one(as(x));
  }
}
