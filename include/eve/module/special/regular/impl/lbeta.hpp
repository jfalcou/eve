//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/special/regular/log_abs_gamma.hpp>

namespace eve::detail
{
template<floating_value T, floating_value U>
EVE_FORCEINLINE auto
lbeta_(EVE_SUPPORTS(cpu_), T a, U b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(lbeta, a, b);
}

template<floating_real_value T>
EVE_FORCEINLINE T
lbeta_(EVE_SUPPORTS(cpu_), T a0, T a1) noexcept requires(has_native_abi_v<T>)
{
  auto y = a0 + a1;
  return log_abs_gamma(a0) + log_abs_gamma(a1) - log_abs_gamma(y);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
lbeta_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::lbeta, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
lbeta_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::lbeta), ts ...);
}
}
