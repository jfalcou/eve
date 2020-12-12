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

#include <eve/function/if_else.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/derivative.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, auto N>
  EVE_FORCEINLINE constexpr T maxmag_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , U const &y) noexcept
  requires(compatible_values<T, U>)
  {
    return arithmetic_call(derivative_type<N>()(maxmag), x, y);
  }

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T maxmag_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
   if constexpr( has_native_abi_v<T> )
    {
      auto ax = eve::abs(x);
      auto ay = eve::abs(y);
      if constexpr(N == 1) return if_else(ax > ay,  one(as(x)), zero);
      if constexpr(N == 2) return if_else(ax < ay,  one(as(x)), zero);
    }
   else
     return apply_over(derivative_type<N>()(maxmag), x, y);
  }
}
