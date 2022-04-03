//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U, floating_value V, auto N>
  EVE_FORCEINLINE  auto if_else_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  requires compatible_values<T, U>&&compatible_values<T, V>
  {
    return arithmetic_call(diff_type<N>()(if_else), a, b, c);
  }

  template<floating_value T, auto N>
  EVE_FORCEINLINE  auto if_else_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , T const &
                            , T const &) noexcept
  {
    if constexpr(N == 2) return if_else(a, T(1), zero);
    else if constexpr(N == 3) return if_else(a, zero, T(1));
  }


  
}
