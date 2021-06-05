//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/betainc.hpp>
#include <eve/function/diff/beta.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/oneminus.hpp>

namespace eve::detail
{
  template<floating_value S, floating_value T, floating_value U, auto N>
  EVE_FORCEINLINE  auto betainc_(EVE_SUPPORTS(cpu_)
                              , diff_type<N> const &
                              , S const &s
                              , T const &a
                              , U const &b) noexcept
  -> decltype(arithmetic_call(diff_type<N>{}(betainc), s, a, b))
  {
    return arithmetic_call(diff_type<N>{}(betainc), s, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T betainc_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T const &s
                                   , T const &x
                                   , T const &y) noexcept
  requires(has_native_abi_v<T>)
  {
    return pow(s, dec(x))*pow(oneminus(s), dec(y))/beta(x, y);
  }
}
