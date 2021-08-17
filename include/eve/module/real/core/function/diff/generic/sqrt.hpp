//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once


#include <eve/function/if_else.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/half.hpp>

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
}
