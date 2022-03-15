//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/special/regular/betainc_inv.hpp>
#include <eve/module/special/diff/betainc.hpp>

namespace eve::detail
{
  template<floating_value S, floating_value T, floating_value U, auto N>
  EVE_FORCEINLINE  auto betainc_inv_(EVE_SUPPORTS(cpu_)
                              , diff_type<N> const &
                              , S const &s
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U> && compatible_values<T, S>
  {
    return arithmetic_call(diff_type<N>{}(betainc_inv), s, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto betainc_inv_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T const &s
                                   , T const &x
                                   , T const &y) noexcept
  requires(has_native_abi_v<T>)
  {
    auto b = betainc_inv(s, x, y);
    return rec(diff_1st(betainc)(b, x, y));
  }
}
