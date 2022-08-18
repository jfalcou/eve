//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/log.hpp>

namespace eve::detail
{
template<floating_real_value T, decorator D>
EVE_FORCEINLINE constexpr T
log_abs_(EVE_SUPPORTS(cpu_), D const&, T x) noexcept
    requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
{
  return D()(eve::log(eve::abs(x)));
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr T
log_abs_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  return log(eve::abs(x));
  ;
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
log_abs_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
requires(std::same_as<U, decltype(eve::abs(t))>)
{
  return mask_op(cond, eve::log_abs, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
log_abs_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
requires(std::same_as<U, decltype(d(log_abs)(t))>)
{
  return mask_op(cond, d(eve::log_abs), t);
}
}
