//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic/regular/lohi.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE constexpr auto lo_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr (sizeof(elt_t) ==  1) //nibbles extraction
    {
      if constexpr(has_native_abi_v<T>)
      {
        using ui_t = as_integer_t<T, unsigned>;
        auto uia0 =  bit_cast(a0, as<ui_t>());
        return ui_t(uia0 & ui_t(0xF));
      }
      else
        return apply_over(lo, a0);
    }
    else
    {
      auto [l, h] = lohi(a0);
      return l;
    }
  }
}
