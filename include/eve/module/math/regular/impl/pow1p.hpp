//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/log1p.hpp>
#include <eve/module/math/regular/pow.hpp>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U>
auto
pow1p_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> decltype(pow(a, b))
{
  return arithmetic_call(pow1p, a, b);
}

template<floating_real_value T>
auto
pow1p_(EVE_SUPPORTS(cpu_), T const& x, T const& y) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    T incx = inc(x);
    return if_else(abs(x) > half(as(x)), pow(incx, y), exp(y * log1p(x)));
  }
  else return apply_over(pow1p, x, y);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value T , real_value U>
EVE_FORCEINLINE auto
pow1p_(EVE_SUPPORTS(cpu_), C const& cond, T const& t, U const& u) noexcept
-> decltype( if_else(cond, pow1p(t, u), t) )
{
  return mask_op(cond, eve::pow1p, t, u);
}
}
