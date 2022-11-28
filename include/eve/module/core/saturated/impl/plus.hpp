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
#include <eve/detail/implementation.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/saturated/add.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
plus_(EVE_SUPPORTS(cpu_),
      saturated_type const&,
      T const& a,
      U const& b) noexcept
-> decltype(plus(a, b))
{
  return saturated(add)(a, b);
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
plus_(EVE_SUPPORTS(cpu_),
      C const& cond,
      saturated_type const&,
      U const& t,
      V const& f) noexcept
requires(std::convertible_to<U, decltype(add(t, f))>)
{
  return mask_op(cond, saturated(add), t, f);
}
}
