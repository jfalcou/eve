//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/pow.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow(x, dec(y))*y;
  }

   template<floating_real_value T>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_)
                                   , diff_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow(x, y)*log(x);
  }
}
