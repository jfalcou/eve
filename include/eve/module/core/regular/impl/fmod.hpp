//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/pedantic/rem.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto
  fmod_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
  {
    return pedantic(rem)(a, b);
  }

  template<conditional_expr C, value T, value U>
  EVE_FORCEINLINE auto fmod_(EVE_SUPPORTS(cpu_), C const &cond, T const &a, U const &b) noexcept
  {
    return mask_op(  cond, pedantic(eve::rem), a, b);
  }

}
