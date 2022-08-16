//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto conj_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    return a;
  }

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
conj_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::conj, t);
}

}
