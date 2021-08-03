//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/constant/false.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_not_real_(EVE_SUPPORTS(cpu_)
                                                        , T const &a) noexcept
  {
    return false_(eve::as(a));
  }
  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_not_real_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return lmask_op(cond, is_not_real, u);
  }
}
