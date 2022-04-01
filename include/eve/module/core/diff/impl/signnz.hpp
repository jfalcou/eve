//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/signnz.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T signnz_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T ) noexcept
  {
    return T(0);
  }


  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto signnz_(EVE_SUPPORTS(cpu_), C const &cond, diff_type<1> const &
                            , U const &t) noexcept
  {
    return mask_op( cond, diff(eve::signnz), t);
  }
}
