//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>

namespace eve::detail
{
  template<callable_options O, relaxed_logical_value T>
  EVE_FORCEINLINE constexpr T logical_or_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
  {
    if  constexpr (relaxed_logical_scalar_value<T>) return a || b;
    else                                            return bit_cast(a.bits() | b.bits(), as<T>{});
  }
}
