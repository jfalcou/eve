//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr as_logical_t<T>
  is_ltz_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
  {
    if constexpr( unsigned_value<T> )
      return false_(eve::as(a));
    else
      return a <  zero(eve::as(a));
  }
}
