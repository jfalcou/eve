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
#include <eve/module/core/regular/countr_zero.hpp>

#include <bit>

#include <type_traits>

namespace eve::detail
{
template<unsigned_value T>
EVE_FORCEINLINE T
countr_one_(EVE_SUPPORTS(cpu_), T const& v) noexcept
{
  if constexpr( scalar_value<T> ) { return T(std::countr_one(v)); }
  else if constexpr( has_native_abi_v<T> ) { return countr_zero(~v); }
  else return apply_over(countr_one, v);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, unsigned_value U>
EVE_FORCEINLINE auto
countr_one_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, countr_one, t);
}
}
