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
      return apply_over(diff_1st(dist), x, y), n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T dist_(EVE_SUPPORTS(cpu_)
                                    , diff_type<2> const &
                                    , T x, T y) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return -sign(x-y);
    else
      return apply_over(diff_1st(dist), x, y);
  }
}
