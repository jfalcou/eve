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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/function/atanpi.hpp>

namespace eve::detail
{

  //  3 params x, m, s
  template<floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto cauchy_(EVE_SUPPORTS(cpu_)
                              , T const &x
                              , U const &m
                              , V const &s ) noexcept
  requires compatible_values<T, U> && compatible_values<T, V>
  {
    return arithmetic_call(cauchy,x, m, s);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto cauchy_( EVE_SUPPORTS(cpu_)
                             , T const &x
                             , T const &m
                             , T const &s
                             ) noexcept

  requires  has_native_abi_v<T>
  {
    return half(as(x)) + atanpi((x-m)/s);
  }

  //  2 params x,  m with s = 1
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto cauchy_(EVE_SUPPORTS(cpu_)
                              , T const &x
                              , U const &m) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(cauchy,x,m);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto cauchy_( EVE_SUPPORTS(cpu_)
                             , T const &x
                             , T const &m
                             ) noexcept

  requires  has_native_abi_v<T>
  {
    return half(as(x)) + atanpi((x-m));
  }

  //  1 param x with s = 1,  m = 0
  template<floating_value T>
  EVE_FORCEINLINE auto cauchy_( EVE_SUPPORTS(cpu_)
                             , T const &x
                              ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return half(as(x)) + atanpi(x);
    }
    else return apply_over(cauchy, x);
  }
}
