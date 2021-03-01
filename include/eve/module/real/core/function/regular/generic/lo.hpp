//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/lohi.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<value T>
  EVE_FORCEINLINE constexpr auto lo_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    auto [l, h] = lohi(a0);
    return l;
  }
}
