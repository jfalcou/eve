//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return as_logical_t<T>(!a);
  }
}
