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
  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr common_logical_t<T, U> logical_and_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
      requires (relaxed_logical_scalar_value<T> && relaxed_logical_scalar_value<U>) || (std::same_as<T, U>)
  {
      // case 1: both are scalar/bool, possibly different.
      if  constexpr (relaxed_logical_scalar_value<T>) return a && b;
      // case 2: both are logical<wide> of the same type. This is required for most archs as they can only perform
      // bitswise operations and convert.
      else                                            return bit_cast(a.bits() & b.bits(), as<T>{});
  }
}
