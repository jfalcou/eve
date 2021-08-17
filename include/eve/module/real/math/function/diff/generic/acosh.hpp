//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/acosh.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sqr.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T acosh_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return rsqrt(dec(sqr((x))));
  }
}
