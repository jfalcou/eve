//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/sindcosd.hpp>
#include <eve/function/derivative.hpp>


namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr kumi::tuple<T, T>
  sindcosd_(EVE_SUPPORTS(cpu_), diff_type<1> const &, T x) noexcept
   {
    if constexpr( has_native_abi_v<T> )
    {
      auto [s, c] = sindcosd(x);
      return {c, -s};
    }
    else
    {
      return apply_over2(sindcosd, x);
    }
  }

}
