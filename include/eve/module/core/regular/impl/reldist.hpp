//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{
  template<value T, value U>
  EVE_FORCEINLINE auto
  reldist_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
  -> decltype(abs(a+b))
    requires(std::is_floating_point_v<eve::underlying_type_t<T>>)
  {
    return dist(a, b)/max(abs(a), abs(b), one(as(a)));
  }

}
