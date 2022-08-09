//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// Basic
template<real_value T>
EVE_FORCEINLINE constexpr T
inc_(EVE_SUPPORTS(cpu_), T const& v) noexcept
{
  if constexpr( has_native_abi_v<T> ) return v + one(eve::as(v));
  else return apply_over(inc, v);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
inc_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::inc, t);
}
}
