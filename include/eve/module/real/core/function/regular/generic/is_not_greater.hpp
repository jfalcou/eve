//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto is_not_greater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  -> decltype(arithmetic_call(is_not_greater, a, b))
  {
    return arithmetic_call(is_not_greater, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE  auto is_not_greater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    if constexpr(integral_value<T>) return is_less_equal(a, b);
    else                            return is_less_equal(a, b) || is_unordered(a, b);
  }
}
