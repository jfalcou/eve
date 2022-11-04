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

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE constexpr T
sqr_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return a * a;
}

template<real_value T>
EVE_FORCEINLINE constexpr T
sqr_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const& a) noexcept
{
  return sqr(a);
}


// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
sqr_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::sqr, t);
}

template<conditional_expr C, pedantic_type const &, value U>
EVE_FORCEINLINE auto
sqr_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::pedantic(eve::sqr), t);
}

}
