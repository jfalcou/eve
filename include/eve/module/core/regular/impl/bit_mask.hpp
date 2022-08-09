//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_nez.hpp>

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE auto
bit_mask_(EVE_SUPPORTS(cpu_), T const& v) noexcept
{
  return is_nez(v).mask();
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
bit_mask_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, bit_mask, t);
}
}
