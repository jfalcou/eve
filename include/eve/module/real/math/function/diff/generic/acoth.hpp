//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/acoth.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/rec.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T acoth_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return rec(oneminus(sqr(x)));
  }
}
