//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/lambert.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/oneminus.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T lambert_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return oneminus(2*x*lambert(x));
  }
}
