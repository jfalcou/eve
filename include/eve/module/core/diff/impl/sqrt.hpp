//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/rsqrt.hpp>
#include <eve/module/core/constant/half.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sqrt_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return half(as(x))*rsqrt(x);
    else
      return apply_over(diff_1st(sqrt), x );
  }
  
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_real_value U>
  EVE_FORCEINLINE auto sqrt_(EVE_SUPPORTS(cpu_), C const &cond, diff_type<1> const &, U const &t) noexcept
  {
    return mask_op( cond, eve::diff(eve::sqrt), t);
  }  
}
