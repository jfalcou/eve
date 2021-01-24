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
#include <eve/function/inc.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/pi.hpp>

namespace eve::detail
{

  //  3 params x, m, s
  template<auto N, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto cauchy_(EVE_SUPPORTS(cpu_)
                               , diff_type<N> const & d
                               , T const &x
                               , U const &m
                               , V const &s ) noexcept
  requires compatible_values<T, U> && compatible_values<T, V>
  {
    return arithmetic_call(d(cauchy),x, m, s);
  }

  template<auto N, floating_value T>
  EVE_FORCEINLINE auto cauchy_( EVE_SUPPORTS(cpu_)
                              , diff_type<N> const &
                              , T const &x
                              , T const &m
                              , T const &s
                              ) noexcept
  requires  has_native_abi_v<T>
  {
    auto xmm = pi(as(x))*(x-m);
    auto tmp =  pi(as(x))*rec(fma(xmm, xmm, sqr(s)));
    if constexpr(N == 1) return s*tmp;
    else if constexpr(N == 2) return -s*tmp;
    else if constexpr(N == 3) return -tmp*xmm;
    else                      return zero(as(x));
  }

  //  2 params x,  m with s = 1
  template<auto N, floating_value T, floating_value U>
  EVE_FORCEINLINE  auto cauchy_(EVE_SUPPORTS(cpu_)
                               , diff_type<N> const & d
                               , T const &x
                               , U const &m) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(d(cauchy),x, m);
  }

  template<auto N, floating_value T>
  EVE_FORCEINLINE auto cauchy_( EVE_SUPPORTS(cpu_)
                              , diff_type<N> const &
                              , T const &x
                              , T const &m
                              ) noexcept

  requires  has_native_abi_v<T>
  {
    auto tmp =  pi(as(x))*rec(inc(sqr(pi(as(x))*(x-m))));
         if constexpr(N == 1) return tmp;
    else if constexpr(N == 2) return -tmp;
    else                      return zero(as(x));
  }

  //  1 param x with s = 1,  m = 0
  template<auto N, floating_value T>
  EVE_FORCEINLINE auto cauchy_( EVE_SUPPORTS(cpu_)
                              , diff_type<N> const & d
                              , T const &x
                              ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(N == 1) return pi(as(x))*rec(inc(sqr(pi(as(x))*x)));
      else                 return zero(as(x));
    }
    else return apply_over(d(cauchy), x);
  }
}
