//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/derivative/pow.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T powm1_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T const &x
                                    , T const &y) noexcept
  {
    return derivative_1st(pow)(x, y);
  }
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T powm1_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<2> const &
                                    , T const &x
                                    , T const &y) noexcept
  {
    return derivative2_nd(pow)(x, y);
  }
}
