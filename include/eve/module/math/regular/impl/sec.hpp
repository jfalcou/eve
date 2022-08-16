//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/cos.hpp>

namespace eve::detail
{
template<floating_real_value T, decorator D>
EVE_FORCEINLINE constexpr auto
sec_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return rec(D()(eve::cos)(a0)); }
  else { return apply_over(D()(sec), a0); }
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
sec_(EVE_SUPPORTS(cpu_), T a0) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return rec(eve::cos(a0)); }
  else { return apply_over(sec, a0); }
}


// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
sec_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::sec, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
sec_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::sec), t);
}
}
