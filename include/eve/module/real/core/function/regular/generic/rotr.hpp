//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/rotl.hpp>

namespace eve::detail
{
  template<integral_value T, integral_value U>
  [[nodiscard]] EVE_FORCEINLINE auto rotr_(EVE_SUPPORTS(cpu_), T const &a0, U const &n) noexcept
  {
    return rotl(a0, U(-n));
  }

}

