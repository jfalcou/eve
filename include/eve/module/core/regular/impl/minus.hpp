//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/signmask.hpp>
#include <eve/module/core/regular/bit_xor.hpp>

#include <type_traits>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE constexpr T
minus_(EVE_SUPPORTS(cpu_), T v) noexcept
{
  if constexpr( simd_value<T> ) return -v;
  else if constexpr( floating_value<T> ) return bit_xor(v, signmask(eve::as(v)));
  else return T {0} - v;
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value U>
EVE_FORCEINLINE auto
minus_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::minus, t);
}

template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
minus_(EVE_SUPPORTS(cpu_),
       C const& cond,
       U const& t,
       V const& f) noexcept -> common_value_t<U, V>
{
  auto substract = [](auto x, auto y) { return x - y; };
  return mask_op(cond, substract, t, f);
}
}
