//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr as_logical_t<T>
is_real_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return true_(eve::as(a));
}

// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
is_real_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
{
  return logical_mask_op(cond, is_real, u);
}
}
