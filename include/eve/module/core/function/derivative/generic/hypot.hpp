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
#include <eve/concept/compatible.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, auto N>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , U const &y) noexcept
  requires(compatible_values<T, U>)
  {
    return arithmetic_call(derivative_type<N>()(hypot), x, y);
  }

  template<floating_real_value T, floating_real_value U, floating_real_value V, auto N>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , U const &y
                                   , V const &z) noexcept
  requires(compatible_values<T, U> && compatible_values<T, V>)
  {
    return arithmetic_call(derivative_type<N>()(hypot), x, y, z);
  }

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
   if constexpr( has_native_abi_v<T> )
    {
     auto k = rec(hypot(x, y));
     if constexpr(N == 1) return x*k;
     else if constexpr(N == 2) return y*k;
    }
   else
     return apply_over(derivative_type<N>()(hypot), x, y);
  }

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , T const &y
                                   , T const &z) noexcept
  {
   if constexpr( has_native_abi_v<T> )
    {
     auto k = rec(hypot(x, y, z));
     if constexpr(N == 1) return x*k;
     else if constexpr(N == 2) return y*k;
     else if constexpr(N == 3) return z*k;
    }
   else
     return apply_over(derivative_type<N>()(hypot), x, y, z);
  }


}
