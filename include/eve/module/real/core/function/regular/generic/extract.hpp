//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<value T, integral_scalar_value I>
  EVE_FORCEINLINE auto extract_(EVE_SUPPORTS(cpu_), T const &a, I i) noexcept
  {
    if constexpr(scalar_value<T>) return a;
    else                          return a.get(i);
  }
}
