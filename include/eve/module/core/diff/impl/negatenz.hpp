//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/constant/zero.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T negatenz_(EVE_SUPPORTS(cpu_)
                                       , diff_type<1> const &
                                       , T, T y) noexcept
  {

    return sign(y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T negatenz_(EVE_SUPPORTS(cpu_)
                                       , diff_type<2> const &
                                       , T x, T ) noexcept
  {
    return zero(as(x));
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<int N, conditional_expr C, floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto negatenz_(EVE_SUPPORTS(cpu_), C const &cond, diff_type<N> const &
                               , T const &t, U const & u ) noexcept
  {
    return mask_op(  cond, eve::diff_nth<N>(eve::negatenz), t, u);
  }

}
