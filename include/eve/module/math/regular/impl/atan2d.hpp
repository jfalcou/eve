//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/atan2.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
atan2d_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
{
  return arithmetic_call(atan2d, a, b);
}

template<floating_real_value T>
EVE_FORCEINLINE auto
atan2d_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept requires has_native_abi_v<T>
{
  return radindeg(atan2(a, b));
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value T, value U>
EVE_FORCEINLINE auto
atan2d_(EVE_SUPPORTS(cpu_), C const& cond, T const& t, U const& u) noexcept
{
  return mask_op(cond, eve::atan2d, t,u);
}

template<conditional_expr C, decorator D, value T, value U>
EVE_FORCEINLINE auto
atan2d_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, T const& t, U const& u) noexcept
{
  return mask_op(cond, d(eve::atan2d), t, u);
}
}
