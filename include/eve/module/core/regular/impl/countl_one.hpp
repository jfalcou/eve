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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/countl_zero.hpp>

#include <bit>

#include <type_traits>

namespace eve::detail
{
template<unsigned_value T>
EVE_FORCEINLINE T
countl_one_(EVE_SUPPORTS(cpu_), T const& v) noexcept
{
  if constexpr( scalar_value<T> ) { return T(std::countl_one(v)); }
  else if constexpr( has_native_abi_v<T> ) { return countl_zero(~v); }
  else return apply_over(countl_one, v);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, unsigned_value U>
EVE_FORCEINLINE auto
countl_one_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, countl_one, t);
}
}
