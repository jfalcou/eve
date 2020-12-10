//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/rec.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
   if constexpr( has_native_abi_v<T> )
    {
     return rec(hypot(x, y))*x;
    }
   else
     return apply_over(derivative_1st(hypot), x, y);
  }


   template<floating_real_value T>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
   if constexpr( has_native_abi_v<T> )
    {
    return rec(hypot(x, y))*y;
    }
   else
     return apply_over(derivative_2nd(hypot), x, y);
  }
}
