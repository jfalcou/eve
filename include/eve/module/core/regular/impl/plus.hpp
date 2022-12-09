//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/add.hpp>

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE T
plus_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return a;
}

template<value T, value U>
EVE_FORCEINLINE auto
plus_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_value_t<T, U>{
  return add(a, b);
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, ordered_value ... U>
EVE_FORCEINLINE auto
plus_(EVE_SUPPORTS(cpu_),
      C const& cond,
      U ... t
     ) noexcept
{
  return mask_op(cond, eve::add, t...);
}

}
