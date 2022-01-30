//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/min.hpp>
#include <eve/module/arithmetic/regular/max.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto dist_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(dist, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE T dist_(EVE_SUPPORTS(cpu_)
                         , T const &a
                         , T const &b) noexcept
  requires has_native_abi_v<T>
  {
    return eve::max(a, b) - eve::min(a, b);
  }
}
