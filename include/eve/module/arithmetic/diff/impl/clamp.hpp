//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/diff/min.hpp>
#include <eve/function/diff/max.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U, floating_value V, auto N>
  EVE_FORCEINLINE  auto clamp_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  requires compatible_values<T, U>&&compatible_values<T, V>
  {
    return arithmetic_call(diff_type<N>()(clamp), a, b, c);
  }

  template<floating_value T, auto N>
  EVE_FORCEINLINE  auto clamp_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , T const &b
                            , T const &c) noexcept
  requires(has_native_abi_v<T>)
  {
         if constexpr(N == 1) return diff_1st(min)(max(a, b), c)*diff_1st(max)(a, b);
    else if constexpr(N == 2) return diff_1st(min)(max(a, b), c)*diff_2nd(max)(a, b);
    else if constexpr(N == 3) return diff_2nd(min)(max(a, b), c);
  }
}
