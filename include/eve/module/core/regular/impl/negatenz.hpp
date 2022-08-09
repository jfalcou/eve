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
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/signnz.hpp>
#include <eve/traits/common_compatible.hpp>

#include <concepts>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE T
negatenz_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept requires has_native_abi_v<T>
{
  if constexpr( signed_value<T> ) { return a * signnz(b); }
  else { return a; }
}

template<real_value T, real_value U>
EVE_FORCEINLINE auto
negatenz_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept requires compatible_values<U, T>
{
  return arithmetic_call(negatenz, a, b);
}
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value T, real_value U>
EVE_FORCEINLINE auto
negatenz_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b) noexcept
{
  return mask_op(cond, eve::negatenz, a, b);
}
}
