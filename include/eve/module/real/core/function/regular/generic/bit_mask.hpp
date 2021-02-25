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
#include <eve/function/is_nez.hpp>

namespace eve::detail
{
  template<value T> EVE_FORCEINLINE auto bit_mask_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return is_nez(v).mask();
  }
}
