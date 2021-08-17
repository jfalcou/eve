//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/exp.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T exp_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T x,  N ) noexcept
  {
    return exp(x);
   }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T exp_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return exp(x);
  }
}
