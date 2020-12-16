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

#include <eve/detail/implementation.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto hypot_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(hypot, a, b);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto hypot_( EVE_SUPPORTS(cpu_)
                             , T const &a
                             , T const &b
                             ) noexcept

  {
    if constexpr(has_native_abi_v<T>) return eve::sqrt(fma(a, a, sqr(b)));
    else                    return  apply_over(hypot, a, b);
  }

  template<floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto hypot_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b
                              , V const &c) noexcept
  requires compatible_values<T, U> &&  compatible_values<T, V>
  {
    return arithmetic_call(hypot, a, b, c);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto hypot_( EVE_SUPPORTS(cpu_)
                             , T const &a
                             , T const &b
                             , T const &c
                             ) noexcept

  {
    if constexpr(has_native_abi_v<T>) return eve::sqrt(fma(a, a, fma(b, b, sqr(c))));
    else                    return  apply_over(hypot, a, b, c);
  }
}
