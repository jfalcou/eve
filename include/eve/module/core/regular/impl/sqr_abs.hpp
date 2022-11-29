//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/sqr.hpp>

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE constexpr auto
sqr_abs_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return sqr(eve::abs(a));
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
sqr_abs_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a) noexcept
{
  return sqr(eve::abs(a));
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
sqr_abs_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
-> decltype(abs(t))
{
  return mask_op(cond, eve::sqr_abs, t);
}
}
