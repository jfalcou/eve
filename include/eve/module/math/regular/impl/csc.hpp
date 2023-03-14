//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/regular/sin.hpp>

namespace eve::detail
{
template<ordered_value T, decorator D>
EVE_FORCEINLINE auto
csc_(EVE_SUPPORTS(cpu_), D const&, T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> ) return rec(D()(sin)(a0));
  else return apply_over(D()(csc), a0);
}

template<value T>
EVE_FORCEINLINE auto
csc_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> ) return rec(sin(a0));
  else return apply_over(csc, a0);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
csc_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::csc, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
csc_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::csc), t);
}
}
