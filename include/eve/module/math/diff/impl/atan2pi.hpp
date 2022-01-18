//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/math/diff/atan2.hpp>
#include <eve/module/math/regular/radinpi.hpp>

namespace eve::detail
{

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T atan2pi_(EVE_SUPPORTS(cpu_)
                                   , diff_type<N> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return radinpi(diff_type<N>()(atan2)(x, y));
  }

}
