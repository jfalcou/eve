//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{

// Recurrence relation for Laguerre polynomials:
template<real_value N, floating_value T>
EVE_FORCEINLINE T
laguerre_(EVE_SUPPORTS(cpu_), successor_type const&, N n, T x, T Ln, T Lnm1) noexcept
{
  auto np1 = inc(n);
  return fms(np1 + n - x, Ln, n * Lnm1) / np1;
}

template<scalar_value I, floating_value T>
EVE_FORCEINLINE auto
laguerre_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
{
  auto p0 = one(as(x));
  if( is_eqz(n) ) return p0;
  auto p1 = oneminus(x);
  auto vc = one(as(x));
  auto c  = one(as(n));
  while( c < n )
  {
    auto p    = p0;
    p0        = p1;
    auto vcp1 = inc(vc);
    p1        = successor(laguerre)(c, x, p0, p);
    vc        = vcp1;
    ++c;
  }
  return p1;
}

template<simd_value I, floating_scalar_value T>
EVE_FORCEINLINE auto
laguerre_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
{
  using f_t = as_wide_t<T, cardinal_t<I>>;
  return laguerre(nn, f_t(x));
}

template<simd_value I, floating_simd_value T>
EVE_FORCEINLINE auto
laguerre_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
{
  if( has_native_abi_v<T> )
  {
    using elt_t = element_type_t<T>;
    auto p0     = one(as(x));
    auto iseqzn = is_eqz(nn);
    if( eve::all(iseqzn) ) return p0;

    auto p1   = oneminus(x);
    auto n    = convert(nn, as<elt_t>());
    auto c    = one(as(n));
    auto test = c < n;
    while( eve::any(test) )
    {
      auto p = p0;
      p0     = p1;
      p1     = if_else(test, successor(laguerre)(c, x, p0, p), p1);
      c      = inc(c);
      test   = c < n;
    }
    return if_else(iseqzn, one, p1);
  }
  else return apply_over(laguerre, nn, x);
}

// Recurrence relation for Laguerre associated polynomials:
template<value N, value L, floating_value T>
EVE_FORCEINLINE auto
laguerre_(EVE_SUPPORTS(cpu_), successor_type const&, N n, L l, T x, T pl, T plm1) noexcept
{
  auto np1 = inc(n);
  auto npl = n + l;
  return ((np1 + npl - x) * pl - npl * plm1) / np1;
}

// associated laguerre polynomials
template<integral_scalar_value M, integral_scalar_value N, floating_value T>
EVE_FORCEINLINE auto
laguerre_(EVE_SUPPORTS(cpu_), N n, M m, T x) noexcept
{
  // Special cases:
  if( m == 0 ) return laguerre(n, x);
  auto p0 = one(as(x));
  if( n == 0 ) return p0;
  auto p1 = inc(m) - x;

  N c = 1;
  while( c < n )
  {
    std::swap(p0, p1);
    p1 = successor(laguerre)(c, m, x, p0, p1);
    ++c;
  }
  return p1;
}

template<value M, value N, floating_value T>
EVE_FORCEINLINE auto
laguerre_(EVE_SUPPORTS(cpu_), N nn, M mm, T x) noexcept
{
  auto iseqzm = is_eqz(mm);
  if( eve::all(iseqzm) ) [[unlikely]] { return laguerre(nn, x); }
  else [[likely]]
  {
    using elt_t = element_type_t<T>;
    auto p0     = one(as(x));
    auto iseqzn = is_eqz(nn);
    if( eve::all(iseqzn) ) [[unlikely]] { return p0; }
    else [[likely]]
    {
      auto m  = convert(mm, as<elt_t>());
      auto p1 = inc(m) - x;

      auto n = convert(nn, as<elt_t>());
      auto c = one(as(n));

      auto test = c < n;
      while( eve::any(test) )
      {
        auto p = p0;
        p0     = p1;
        p1     = if_else(test, successor(laguerre)(c, m, x, p0, p), p1);
        c      = inc(c);
        test   = c < n;
      }
      return if_else(iseqzn, one, if_else(iseqzm, laguerre(nn, x), p1));
    }
  }
}
}
