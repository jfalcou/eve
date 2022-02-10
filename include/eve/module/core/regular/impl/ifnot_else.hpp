//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<value T, value U, value V>
  EVE_FORCEINLINE constexpr auto ifnot_else_(EVE_SUPPORTS(cpu_)
             , T const &cond
             , U const &t
             , V const &f) noexcept
  requires compatible_values<U, V>
  {
    return if_else(cond, f, t);
  }
}

