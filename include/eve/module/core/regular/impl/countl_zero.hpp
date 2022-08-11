//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/zero.hpp>

#include <bit>

#include <type_traits>

namespace eve::detail
{
template<unsigned_value T>
EVE_FORCEINLINE T
countl_zero_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  if constexpr( scalar_value<T> ) return T(std::countl_zero(x));
  else return map(countl_zero, x);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, unsigned_value U>
EVE_FORCEINLINE auto
countl_zero_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, countl_zero, t);
}
}
