//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sinc_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    auto [s, c] = sincos(x);
    return if_else(is_eqz(x), zero, fms(x, c, s)/sqr(x));
  }
}
