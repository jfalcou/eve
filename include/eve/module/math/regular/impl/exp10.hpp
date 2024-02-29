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
  template<floating_ordered_value T, decorator D>
  EVE_FORCEINLINE constexpr T
  exp10_(EVE_SUPPORTS(cpu_), D const&, T x) noexcept
  requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
  {
    
  }
}
