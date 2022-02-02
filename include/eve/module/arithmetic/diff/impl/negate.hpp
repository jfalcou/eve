//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T negate_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T, T y) noexcept
  {

    return sign(y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T negate_(EVE_SUPPORTS(cpu_)
                                    , diff_type<2> const &
                                    , T x, T ) noexcept
  {

    return zero(as(x));
  }
}
