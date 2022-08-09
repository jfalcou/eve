//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/acos.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto asec_(EVE_SUPPORTS(cpu_), D const &, T const &a) noexcept
      requires(is_one_of<D>(types<regular_type, raw_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      return D()(acos)(rec(a));
    }
    else
    {
      return apply_over(D()(eve::asec), a);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto asec_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return asec(regular_type{}, a);
  }
}
