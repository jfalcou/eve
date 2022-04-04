//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/pedantic/rem.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr auto fmod_(EVE_SUPPORTS(cpu_)
                                      , T const &a, T const &b) noexcept
  {
    return pedantic(rem)(a, b);
  }


  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto fmod_(EVE_SUPPORTS(cpu_), C const &cond
                               , T const &t, U const & u ) noexcept
  {
    return mask_op(  cond, eve::fmod, t, u);
  }
}
