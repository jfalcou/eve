//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math/regular/atan.hpp>
#include <eve/module/math/regular/sinh.hpp>

namespace eve::detail
{

template<ordered_value T>
EVE_FORCEINLINE constexpr auto
gd_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return atan(sinh(x)); }
  else return apply_over(gd, x);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
gd_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::gd, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
gd_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::gd), t);
}
}
