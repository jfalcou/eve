//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/any.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE bool none_(EVE_SUPPORTS(cpu_)
                           , T const &v) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      return !v;
    }
    else if constexpr(simd_value<T>)
    {
      return !eve::any(v);
    }
  }

  template<simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE bool none_(EVE_SUPPORTS(cpu_), C const &cond, T const &v) noexcept
  {
    return !eve::any[cond](v);
  }
}
