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
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve::detail
{
template<real_value T, real_value U, real_value V>
EVE_FORCEINLINE auto
fma_(EVE_SUPPORTS(cpu_),
     T const& a,
     U const& b,
     V const& c) noexcept
-> common_value_t<T, U, V>
{
  using r_t = common_value_t<T, U, V>;
  return arithmetic_call(fma, r_t(a), r_t(b), r_t(c));
}

template<value T> // fallback never taken if proper intrinsics are at hand
EVE_FORCEINLINE T
fma_(EVE_SUPPORTS(cpu_), T const& a, T const& b, T const& c) noexcept
{
  return a * b + c;
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, real_value T, real_value U, real_value V>
EVE_FORCEINLINE auto
fma_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b, V const& c) noexcept
-> common_value_t<T, U, V>
{
  using r_t = common_value_t<T, U, V>;
  return mask_op(cond, eve::fma, r_t(a), r_t(b), r_t(c));
}

}
