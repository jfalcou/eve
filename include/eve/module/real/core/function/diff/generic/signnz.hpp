//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/signnz.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T signnz_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T ) noexcept
  {
    return T(0);
  }
}
