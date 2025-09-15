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
#include <eve/module/core/regular/any.hpp>

namespace eve::detail
{
  template <callable_options O, typename T>
  EVE_FORCEINLINE auto none_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
  {
    return !any[opts](v);
  }
}
