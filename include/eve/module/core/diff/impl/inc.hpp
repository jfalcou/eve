//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T inc_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(is_eqz(n), inc(x), if_else(n == 1, one(as(x)), zero));
    }
    else
      return apply_over(diff_1st(inc), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T inc_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x) noexcept
  {

    return one(as(x));
  }
}
