//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
arg_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return if_else(is_negative(a), pi(eve::as(a)), eve::zero); }
  else { return apply_over(arg, a); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
arg_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::arg, t);
}
}
