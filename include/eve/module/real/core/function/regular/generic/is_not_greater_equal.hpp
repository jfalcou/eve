//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto is_not_greater_equal_(EVE_SUPPORTS(cpu_)
                                             , T const &a
                                             , U const &b) noexcept
  -> decltype(arithmetic_call(is_not_greater_equal, a, b))
  {
    return arithmetic_call(is_not_greater_equal, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE  auto is_not_greater_equal_(EVE_SUPPORTS(cpu_)
                                             , T const &a
                                             , T const &b) noexcept
  {
    if constexpr(integral_value<T>) return is_less(a, b);
    else                            return is_less(a, b) || is_unordered(a, b);
  }
}
