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
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
template<value T, value U, value V>
EVE_FORCEINLINE constexpr auto
ifnot_else_(EVE_SUPPORTS(cpu_),
            T const& cond,
            U const& t,
            V const& f) noexcept
-> decltype(if_else(cond, f, t))
{
  return if_else(cond, f, t);
}
}
