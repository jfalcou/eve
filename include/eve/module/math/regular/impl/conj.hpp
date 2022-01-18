//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto conj_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    return a;
  }
}
