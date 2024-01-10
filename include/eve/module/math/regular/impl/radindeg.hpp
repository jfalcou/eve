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
  EVE_FORCEINLINE constexpr auto
  radindeg_(EVE_SUPPORTS(cpu_), T const& a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto radradindeg  = ieee_constant<0x1.ca5dc20p+5f, 0x1.ca5dc1a63c1f8p+5>(eve::as<T>{});
      auto radradindegr = ieee_constant<0x1.670f800p-21f, 0x1.1e7ab456405f8p-49>(eve::as<T>{});
      return fma(a, radradindegr, a * radradindeg);
    }
    else return apply_over(radindeg, a);
  }
  
  
// -----------------------------------------------------------------------------------------------
// Masked cases
  template<conditional_expr C, value U>
  EVE_FORCEINLINE auto
  radindeg_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
  {
    return mask_op(cond, eve::radindeg, t);
  }
  
  template<conditional_expr C, decorator D, value U>
  EVE_FORCEINLINE auto
  radindeg_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
  {
    return mask_op(cond, d(eve::radindeg), t);
  }
}
