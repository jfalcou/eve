//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
template<floating_value T, floating_value U>
EVE_FORCEINLINE auto
lbeta_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(lbeta, a, b);
}

template<floating_ordered_value T>
EVE_FORCEINLINE T
lbeta_(EVE_SUPPORTS(cpu_), T a0, T a1) noexcept requires(has_native_abi_v<T>)
{
  auto y = a0 + a1;
  return log_abs_gamma(a0) + log_abs_gamma(a1) - log_abs_gamma(y);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename T0, typename ... Ts>
EVE_FORCEINLINE auto
lbeta_(EVE_SUPPORTS(cpu_), C const& cond, T0 t0, Ts ... ts) noexcept
-> decltype(if_else(cond, lbeta(t0, ts...), t0))
{
  return mask_op(cond, eve::lbeta, t0, ts ...);
}

template<conditional_expr C, decorator D, typename T0, typename  ... Ts>
EVE_FORCEINLINE auto
lbeta_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, T0 t0, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::lbeta), t0, ts ...);
}
}
