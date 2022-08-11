//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/rem.hpp>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U>
EVE_FORCEINLINE constexpr auto
remainder_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  return to_nearest(rem)(a, b);
}
}
