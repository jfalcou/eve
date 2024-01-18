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
  template<ordered_value N, floating_value T, callable_options O>
  EVE_FORCEINLINE T
  laguerre_(EVE_REQUIRES(cpu_), O const&, N n, T x, T Ln, T Lnm1) 
   requires(O::contains(successor2))
  {
    auto np1 = inc(n);
    return fms(np1 + n - x, Ln, n * Lnm1) / np1;
  }

  //  Laguerre polynomials:
  template<typename I, typename T, callable_options O>
  EVE_FORCEINLINE auto
  laguerre_(EVE_REQUIRES(cpu_), O const&, I n, T x) 
  {
    if constexpr(scalar_value<I>)
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
        p1        = laguerre[successor](c, x, p0, p);
        vc        = vcp1;
        ++c;
      }
      return p1;
    }
    else if constexpr(simd_value<I>)
    {
      if constexpr(scalar_value<T>)
      {
        using f_t = as_wide_t<T, cardinal_t<I>>;
        return laguerre(n, f_t(x));
      }
      else if constexpr(simd_value<T>)
      {
        if( has_native_abi_v<T> )
        {
          using elt_t = element_type_t<T>;
          auto p0     = one(as(x));
          auto iseqzn = is_eqz(n);
          if( eve::all(iseqzn) ) return p0;

          auto p1   = oneminus(x);
          auto nn    = convert(n, as<elt_t>());
          auto c    = one(as(nn));
          auto test = c < nn;
          while( eve::any(test) )
          {
            auto p = p0;
            p0     = p1;
            p1     = if_else(test, laguerre[successor](c, x, p0, p), p1);
            c      = inc(c);
            test   = c < nn;
          }
          return if_else(iseqzn, one, p1);
        }
        else return apply_over(laguerre, n, x);
      }
    }
  }

  // Recurrence relation for Laguerre associated polynomials:
  template< typename N, typename L, typename T, callable_options O> //successor associated option
  EVE_FORCEINLINE T
  laguerre_(EVE_REQUIRES(cpu_), O const&, N n, L l, T x, T pl, T plm1)
    requires(O::contains(successor2) && O::contains(associated2))
  {
    auto np1 = inc(n);
    auto npl = n + l;
    return ((np1 + npl - x) * pl - npl * plm1) / np1;
  }

 // associated laguerre polynomials
  template<typename M, typename N, typename T, callable_options O>
  as_wide_as_t<T, common_value_t<M, N>>
  laguerre_(EVE_REQUIRES(cpu_), O const&, N nn, M mm, T x)
    requires(O::contains(associated2))
  {
    if constexpr(integral_scalar_value<M> && integral_scalar_value<N>)
    {
      if( mm == 0 ) return laguerre(nn, x);
      auto p0 = one(as(x));
      if( nn == 0 ) return p0;
      auto p1 = inc(mm) - x;

      N c = 1;
      while( c < nn )
      {
        std::swap(p0, p1);
        p1 = laguerre[associated][successor](c, mm, x, p0, p1);
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
        auto p0     = one(as<r_t>());
        auto iseqzn = is_eqz(nn);
        if( eve::all(iseqzn) )  { return r_t(p0); }
        else
        {
          auto m  = convert(mm, as<elt_t>());
          auto p1 = inc(m) - r_t(x);

          auto n = convert(nn, as<elt_t>());
          auto c = one(as<r_t>());

          auto test = c < n;
          while( eve::any(test) )
          {
            auto p = p0;
            p0     = p1;
            p1     = if_else(test, laguerre[associated][successor](c, m, x, p0, p), p1);
            c      = inc(c);
            test   = c < n;
          }
          return if_else(iseqzn, one, if_else(iseqzm, laguerre(nn, x), p1));
        }
      }
    }
  }
}
