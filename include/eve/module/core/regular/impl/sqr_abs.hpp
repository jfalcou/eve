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
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
sqr_abs_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return sqr(a);
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
sqr_abs_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a) noexcept
{
  return sqr(a);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
sqr_abs_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
requires(std::convertible_to<U, decltype(abs(t))>)
{
  return mask_op(cond, eve::sqr_abs, t);
}
}
