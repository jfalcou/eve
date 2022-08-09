//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE  auto geommean_(EVE_SUPPORTS(cpu_)
                                 ,  pedantic_type const&
                                 , T a
                                 , U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(geommean), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE  T geommean_(EVE_SUPPORTS(cpu_)
                              ,  pedantic_type const&
                              , T a
                              , T b) noexcept
  requires has_native_abi_v<T>
  {
    auto m = max(a, b);
    auto im = if_else(is_nez(m), rec(m), m);
    auto z = min(a, b)*im;
    return if_else(is_nltz(a) || is_nltz(b), sqrt(z)*m, allbits);
  }
  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto geommean_(EVE_SUPPORTS(cpu_), C const &cond, pedantic_type const &
                                , U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, pedantic(eve::geommean), t, f);
  }

}
