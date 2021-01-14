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

#include <eve/function/oneminus.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/derivative/plus.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T oneminus_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(is_eqz(n), oneminus(x), if_else(is_equal(n, 1u), one(as(x)), zero));
    }
    else
      return apply_over(diff_1st(oneminus), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T oneminus_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x) noexcept
  {

    return one(as(x));
  }
}
