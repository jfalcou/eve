//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE constexpr T
quadrant_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    using u_t =  underlying_type_t<T>;
    if constexpr( floating_value<u_t> )
    {
      T b = a * T(0.25);
      return (b - floor(b)) * T(4);
    }
    else if constexpr( integral_value<T> ) return (a & T(3));
  }
  else return apply_over(quadrant, a);
}
}
