//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/exp_int.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/dec.hpp>

namespace eve::detail
{

  template<floating_real_value T, real_value N>
  EVE_FORCEINLINE constexpr T exp_int_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , N const &n
                                  , T const &x) noexcept
  {
    return -exp_int(dec(n), x);
  }
}
