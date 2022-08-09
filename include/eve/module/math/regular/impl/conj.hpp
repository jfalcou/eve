//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
