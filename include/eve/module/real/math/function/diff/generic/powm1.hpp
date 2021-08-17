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
  EVE_FORCEINLINE constexpr T powm1_(EVE_SUPPORTS(cpu_)
                                    , diff_type<N> const &
                                    , T const &x
                                    , T const &y) noexcept
  {
    return diff_type<N>()(eve::pow)(x, y);
  }
}
