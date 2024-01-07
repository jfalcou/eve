//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE constexpr T
deginrad_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto ridh = ieee_constant<T>(0x1.1de0000p-6f, 0x1.1df46a0000000p-6);
    auto ridl = ieee_constant<T>(0x1.46a2520p-18f, 0x1.294e9c8ae0ec6p-33);
    return fma(a, ridl, a * ridh);
  }
  else return apply_over(deginrad, a);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
deginrad_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::deginrad, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
deginrad_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::deginrad), t);
}
}
