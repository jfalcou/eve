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

#include <eve/function/diff/pow.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T powm1_(EVE_SUPPORTS(cpu_)
                                    , diff_type<N> const &
                                    , T const &x
                                    , T const &y) noexcept
  {
    return diff_type<N>()(eve::pow)(x, y);
  }
}
