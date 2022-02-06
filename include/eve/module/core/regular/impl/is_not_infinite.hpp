//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_finite.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/logical_not.hpp>
#include <eve/traits/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_not_infinite_(EVE_SUPPORTS(cpu_)
                                                       , T const &a) noexcept
  {
    return eve::is_finite(a) || is_nan(a);
  }
  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_not_infinite_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return logical_mask_op(cond, is_not_infinite, u);
  }
}
