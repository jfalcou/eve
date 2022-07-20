//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
// Recurrence relation for hermite polynomials:
template<real_value N, floating_value T>
EVE_FORCEINLINE T
hermite_(EVE_SUPPORTS(cpu_), successor_type const&, N n, T x, T hn, T hnm1) noexcept
{
  auto z = fms(x, hn, T(n) * hnm1);
  return z + z;
}

template<integral_scalar_value I, floating_real_scalar_value T>
EVE_FORCEINLINE auto
hermite_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
{
  auto p0 = one(as(x));
  if( is_eqz(n) ) return p0;
  auto p1 = x + x;
  auto c  = one(as(n));
  while( c < n )
  {
    std::swap(p0, p1);
    p1 = successor(hermite)(c, x, p0, p1);
    ++c;
  }
  return p1;
}

template<integral_scalar_value I, floating_real_simd_value T>
EVE_FORCEINLINE auto
hermite_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
{
  T p0 = one(as(x));
  if( is_eqz(n) ) return p0;
  T p1 = x + x;
  I c  = one(as(n));
  while( c < n )
  {
    std::swap(p0, p1);
    p1 = successor(hermite)(c, x, p0, p1);
    ++c;
  }
  return p1;
}

template<integral_simd_value I, floating_real_scalar_value T>
EVE_FORCEINLINE auto
hermite_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
{
  using f_t = as_wide_t<T, cardinal_t<I>>;
  return hermite(nn, f_t(x));
}

template<integral_simd_value I, floating_real_simd_value T>
EVE_FORCEINLINE auto
hermite_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
{
  using elt_t = element_type_t<T>;
  auto p0     = one(as(x));
  auto iseqzn = is_eqz(nn);
  if( eve::all(iseqzn) ) return p0;
  auto p1   = add[!iseqzn](x, x);
  auto n    = convert(nn, as<elt_t>());
  auto c    = one(as(n));
  auto test = c < n;
  auto swap = [](auto cond, auto& a, auto& b) { // TODO Conditionnal swap with shuffles
    auto c = a;
    a      = if_else(cond, b, a);
    b      = if_else(cond, c, b);
  };

  while( eve::any(test) )
  {
    swap(test, p0, p1);
    p1   = if_else(test, successor(hermite)(c, x, p0, p1), p1);
    c    = inc[test](c);
    test = c < n;
  }
  return if_else(iseqzn, one, p1);
}

template<int N, floating_value T>
EVE_FORCEINLINE auto
hermite_(EVE_SUPPORTS(cpu_), std::integral_constant<int, N> const&, T x) noexcept
{
  if constexpr( N < 0 ) return zero(as(x));
  else if constexpr( N == 0 ) return one(as(x));
  else if constexpr( N == 1 ) return x + x;
  else if constexpr( N == 2 ) return dec(sqr(x)) * 2;
  else if constexpr( N == 3 ) return 4 * x * (sqr(x) - 3);
  else if constexpr( N == 4 )
  {
    auto x2 = sqr(x + x);
    return fnma(T(12), dec(x2), sqr(x2));
  }
  else return hermite(N, x);
}
}
