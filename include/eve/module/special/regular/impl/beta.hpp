//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/module/special/regular/signgam.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
template<floating_ordered_value T, floating_ordered_value U>
EVE_FORCEINLINE auto
beta_(EVE_SUPPORTS(cpu_), T a0, U a1) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(beta, a0, a1);
}

template<floating_ordered_value T>
EVE_FORCEINLINE T
beta_(EVE_SUPPORTS(cpu_), T a0, T a1) noexcept
{
  auto y    = a0 + a1;
  auto sign = eve::signgam(a0) * eve::signgam(a1) * eve::signgam(y);
  return sign * exp(log_abs_gamma(a0) + log_abs_gamma(a1) - log_abs_gamma(y));
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C,  typename T0, typename ... Ts>
EVE_FORCEINLINE auto
beta_(EVE_SUPPORTS(cpu_), C const& cond, T0 t0, Ts ... ts) noexcept
-> decltype(if_else(cond, beta(t0, ts...), t0)){
  return mask_op(cond, eve::beta, t0, ts ...);
}

template<conditional_expr C, decorator D,  typename T0, typename  ... Ts>
EVE_FORCEINLINE auto
beta_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, T0 t0, Ts ... ts) noexcept
-> decltype(if_else(cond, beta(t0, ts...), t0)){
  return mask_op(cond, d(eve::beta), t0, ts ...);
}
}
