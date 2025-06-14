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
#include <eve/module/core/regular/logical_ornot.hpp>

namespace eve::detail
{
  template<callable_options O, relaxed_logical_value T>
  EVE_FORCEINLINE constexpr T logical_notor_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
  {
    return logical_ornot(b, a);
  }

  template<callable_options O, conditional_expr C, relaxed_logical_value T>
  EVE_FORCEINLINE constexpr T logical_notor_(EVE_REQUIRES(cpu_), C const& cx, O const&, T a, T b) noexcept
  {
    return logical_ornot[cx](b, a);
  }
}
