//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T fmod_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x, T ) noexcept
  {
    return one(as(x));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T fmod_(EVE_SUPPORTS(cpu_)
                                    , diff_type<2> const &
                                    , T x, T y) noexcept
  {
    return minus(trunc(x/y));
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<int N, conditional_expr C, floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto fmod_(EVE_SUPPORTS(cpu_), C const &cond, diff_type<N> const &
                               , T const & t, U const & u ) noexcept
  {
    return mask_op(  cond, eve::diff_nth<N>(eve::fmod), t, u);
  }
}
