//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/sqr.hpp>


namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sqr_abs_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return sqr(a);
  }
}
