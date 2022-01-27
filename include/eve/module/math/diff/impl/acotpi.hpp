//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math/diff/acot.hpp>
#include <eve/module/math/regular/radinpi.hpp>


namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T acotpi_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return  radinpi(diff(acot)(x));
  }
}
