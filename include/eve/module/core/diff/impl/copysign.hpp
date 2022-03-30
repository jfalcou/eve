//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/constant/zero.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T copysign_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T const &
                                   , T const &y) noexcept
  {
    return sign(y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T copysign_(EVE_SUPPORTS(cpu_)
                                   , diff_type<2> const &
                                   , T const &x
                                   , T const &) noexcept
  {
    return  zero(as(x));
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<int N, conditional_expr C, floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto copysign_(EVE_SUPPORTS(cpu_), C const &cond, diff_type<N> const &
                               , T const &t, U const & u ) noexcept
  {
    return mask_op(  cond, eve::diff_nth<N>(eve::copysign), t, u);
  }

}
