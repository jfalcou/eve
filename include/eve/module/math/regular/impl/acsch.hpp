//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/asinh.hpp>

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE constexpr auto
acsch_(EVE_SUPPORTS(cpu_), T const& x) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return asinh(rec(x)); }
  else { return apply_over(acsch, x); }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
acsch_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::acsch, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
acsch_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::acsch), t);
}
}
