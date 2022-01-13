//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/sign.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T dist_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x, T y) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return sign(x-y);
    else
      return apply_over(diff_1st(dist), x, y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T dist_(EVE_SUPPORTS(cpu_)
                                    , diff_type<2> const &
                                    , T x, T y) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return sign(y-x);
    else
      return apply_over(diff_2nd(dist), x, y);
  }
}
