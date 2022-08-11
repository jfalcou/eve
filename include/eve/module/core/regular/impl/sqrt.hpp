//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/sqrtvalmax.hpp>
#include <eve/module/core/decorator/raw.hpp>

#include <cmath>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE constexpr T
sqrt_(EVE_SUPPORTS(cpu_), raw_type const&, T const& a) noexcept
{
  return eve::sqrt(a);
}

template<real_value T>
EVE_FORCEINLINE constexpr T
sqrt_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_aggregated_abi_v<T> ) { return aggregate(eve::sqrt, a0); }
  else if constexpr( scalar_value<T> ) { return std::sqrt(a0); }
  else { return map(eve::sqrt, a0); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
sqrt_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::sqrt, t);
}
}
