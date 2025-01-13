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
  EVE_FORCEINLINE constexpr common_logical_t<T, U> logical_andnot_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
    requires (relaxed_logical_scalar_value<T> && relaxed_logical_scalar_value<U>) || (std::same_as<T, U>)
  {
    return a && !b;
  }
}
