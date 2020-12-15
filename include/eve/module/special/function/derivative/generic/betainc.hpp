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

#include <eve/function/betainc.hpp>
#include <eve/function/derivative/beta.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/oneminus.hpp>

namespace eve::detail
{
  template<floating_value S, floating_value T, floating_value U, auto N>
  EVE_FORCEINLINE  auto betainc_(EVE_SUPPORTS(cpu_)
                              , derivative_type<N> const &
                              , S const &s
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U> && compatible_values<T, S>
  {
    return arithmetic_call(derivative_type<N>{}(betainc), s, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T betainc_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T const &s
                                   , T const &x
                                   , T const &y) noexcept
  requires(has_native_abi_v<T>)
  {
    return pow(s, dec(x))*pow(oneminus(s), dec(y))/beta(x, y);
  }
}
