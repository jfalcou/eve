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
  constexpr EVE_FORCEINLINE auto laguerre_successor(auto n, auto l, auto x, auto pl, auto plm1)
  {
    auto np1 = inc(n);
    auto npl = n + l;
    return fms(np1 + npl - x, pl, npl * plm1) / np1;
  }

  template<typename N>
  constexpr EVE_FORCEINLINE auto laguerre_successor(N n, auto x, auto Ln, auto Lnm1)
  {
    return laguerre_successor(n,N{0},x,Ln,Lnm1);
  }

  //  Laguerre polynomials:
  template<callable_options O, typename I, typename T>
  constexpr auto laguerre_(EVE_REQUIRES(cpu_), O const&, I n, T x)
  {
    if constexpr(scalar_value<I>)
    {
      auto p0 = one(as{x});
      if( is_eqz(n) ) return p0;
      auto p1 = oneminus(x);
      auto vc = one(as{x});
      auto c  = one(as{n});
      while( c < n )
      {
        auto p    = p0;
        p0        = p1;
        auto vcp1 = inc(vc);
        p1        = laguerre_successor(c, x, p0, p);
        vc        = vcp1;
        ++c;
      }
      return p1;
    }
    else
    {
      if constexpr(scalar_value<T>)
      {
        return laguerre(n, as_wide_t<T, cardinal_t<I>>(x));
      }
      else if constexpr(simd_value<T>)
      {
        using elt_t = element_type_t<T>;
        auto p0     = one(as{x});
        auto iseqzn = is_eqz(n);
        if( eve::all(iseqzn) ) return p0;

        auto p1   = oneminus(x);
        auto nn    = convert(n, as<elt_t>{});
        auto c    = one(as{nn});
        auto test = c < nn;
        while( eve::any(test) )
        {
          auto p = p0;
          p0     = p1;
          p1     = if_else(test, laguerre_successor(c, x, p0, p), p1);
          c      = inc(c);
          test   = c < nn;
        }
        return if_else(iseqzn, one, p1);
      }
    }
  }

  // associated laguerre polynomials
  template<typename M, typename N, typename T, callable_options O>
  constexpr as_wide_as_t<T, common_value_t<M, N>>
  laguerre_(EVE_REQUIRES(cpu_), O const&, N nn, M mm, T x)
  requires(O::contains(associated))
  {
    if constexpr(integral_scalar_value<M> && integral_scalar_value<N>)
    {
      if( mm == 0 ) return laguerre(nn, x);
      auto p0 = one(as{x});
      if( nn == 0 ) return p0;
      auto p1 = inc(mm) - x;

      N c = 1;
      while( c < nn )
      {
        std::swap(p0, p1);
        p1 = laguerre_successor(c, mm, x, p0, p1);
        ++c;
      }
      return p1;
    }
    else
    {
      using r_t = as_wide_as_t<T, common_value_t<M, N>>;
      auto iseqzm = is_eqz(mm);
      if( eve::all(iseqzm) ) { return laguerre(nn, x); }
      else
      {
        using elt_t = element_type_t<T>;
        auto p0     = one(as<r_t>{});
        auto iseqzn = is_eqz(nn);
        if( eve::all(iseqzn) )  { return r_t(p0); }
        else
        {
          auto m  = convert(mm, as<elt_t>{});
          auto p1 = inc(m) - r_t(x);

          auto n = convert(nn, as<elt_t>{});
          auto c = one(as<r_t>{});

          auto test = c < n;
          while( eve::any(test) )
          {
            auto p = p0;
            p0     = p1;
            p1     = if_else(test, laguerre_successor(c, m, x, p0, p), p1);
            c      = inc(c);
            test   = c < n;
          }
          return if_else(iseqzn, one, if_else(iseqzm, laguerre(nn, x), p1));
        }
      }
    }
  }
}
