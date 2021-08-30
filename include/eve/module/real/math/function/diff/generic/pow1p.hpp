//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/diff/pow.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T pow1p_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T const &x
                                    , T const &y) noexcept
  {
    return pow1p(x, dec(y))*y;
  }

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T pow1p_(EVE_SUPPORTS(cpu_)
                                    , diff_type<2> const &
                                    , T const &x
                                    , T const &y) noexcept
  {
    return pow1p(x, y)*lo1p(x);
  }


}
