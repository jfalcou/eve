//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/add.hpp>

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE auto
plus_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return a;
}

template<value T, value U>
EVE_FORCEINLINE auto
plus_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept requires compatible_values<T, U>
{
  return a + b;
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, real_value ... U>
EVE_FORCEINLINE auto
plus_(EVE_SUPPORTS(cpu_),
      C const& cond,
      U ... t
     ) noexcept
{
  return mask_op(cond, eve::add, t...);
}

}
