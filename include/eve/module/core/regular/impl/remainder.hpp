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
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/rem.hpp>

namespace eve::detail
{
template<floating_ordered_value T, floating_ordered_value U>
EVE_FORCEINLINE constexpr auto
remainder_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  return to_nearest(rem)(a, b);
}
}
