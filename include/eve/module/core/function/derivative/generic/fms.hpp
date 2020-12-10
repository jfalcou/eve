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

#include <eve/constant/mone.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U, floating_value V, auto N>
  EVE_FORCEINLINE  auto fms_(EVE_SUPPORTS(cpu_)
                            , derivative_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  requires compatible_values<T, U>&&compatible_values<T, V>
  {
    return arithmetic_call(derivative_type<N>()(fms), a, b, c);
  }

  template<floating_value T, auto N>
  EVE_FORCEINLINE  auto fms_(EVE_SUPPORTS(cpu_)
                            , derivative_type<N> const &
                            , T const &a
                            , T const &b
                            , T const &c) noexcept
  requires(has_native_abi_v<T>)
  {
    if constexpr(N == 1) return b;
    if constexpr(N == 2) return a;
    if constexpr(N == 3) return mone(as(c));
  }
}
