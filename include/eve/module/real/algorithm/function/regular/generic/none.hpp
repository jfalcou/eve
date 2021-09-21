//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/any.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<logical_simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE bool none_(EVE_SUPPORTS(cpu_), C const &cond, T const &v) noexcept
  {
    return !eve::any[cond](v);
  }

  EVE_FORCEINLINE bool none_(EVE_SUPPORTS(cpu_), bool v) noexcept
  {
    return !v;
  }

  template<value T>
  EVE_FORCEINLINE bool none_(EVE_SUPPORTS(cpu_), logical<T> const &v) noexcept
  {
    if constexpr ( scalar_value<T> ) return !v;
    else                             return eve::none[ignore_none](v);
  }
}
