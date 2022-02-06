//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/bessel/regular/cyl_bessel_i0.hpp>
#include <eve/module/bessel/regular/cyl_bessel_i1.hpp>
#include <eve/module/bessel/detail/kernel_bessel_ik.hpp>
#include <eve/module/bessel/detail/kernel_bessel_ij_small.hpp>

/////////////////////////////////////////////////////////////////////////////////
// These routines are detail of the computation of modifiesd cylindrical bessel
// fnctions of the first kind.                  .
// They are not meant to be called directly,  as their validities depends on
// n and x ranges values which are not tested on entry.
// The inspiration is from boost math
/////////////////////////////////////////////////////////////////////////////////
namespace eve::detail
{

  /////////////////////////////////////////////////////////////////////////
  // bessel_i
  template<floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_i (T n, T x) noexcept
  {
    auto br_small =  [](auto n,  auto x)
      {
        return bessel_i_small_z_series(n, x);
      };

    auto br_medium =  [](auto n,  auto x)
      {
        auto [in, ipn, kn, kpn] = kernel_bessel_ik(n, x);
        return in;
      };
    auto br_half =  [](auto x)
      {
        if(eve::any(x >= maxlog(as(x))))
        {
          auto ex = eve::exp(x/2);
          return ex*(ex*rsqrt(x*twopi(as(x))));
        }
        else return rsqrt(x*pio_2(as(x)))*sinh(x);
      };

    if constexpr(scalar_value<T>)
    {
      if (is_ngez(x))                               return nan(as(x));
      if (is_eqz(x))                                return (n == 0) ? one(as(x)) : zero(as(x));
      if (x == inf(as(x)))                          return inf(as(x));
      if (n == T(0.5))                              return br_half(x);       //cyl_bessel_i order 0.5
      if (n == 0)                                   return cyl_bessel_i0(x); //cyl_bessel_i0(x);
      if (n == 1)                                   return cyl_bessel_i1(x); //cyl_bessel_i1(x);
      if (x*4 < n)                                  return br_small(n, x);   // serie
      return br_medium(n, x);                                                // general
    }
    else
    {
      auto r = nan(as(x));
      auto isinfx = x == inf(as(x));
      r =  if_else(isinfx, inf(as(x)), allbits);
      x = if_else(isinfx, mone, x);
      auto iseqzx = is_eqz(x);
      auto iseqzn = is_eqz(n);
      if (eve::any(iseqzx))
      {
        r = if_else(iseqzx, if_else(iseqzn, zero, one(as(x))), r);
      }
      if (eve::any(iseqzn))
      {
        r = if_else(iseqzn, cyl_bessel_i0(x), r);
      }
      auto iseq1n = n == one(as(n));
      if (eve::any(iseq1n))
      {
        r = if_else(n == one(as(n)), cyl_bessel_i1(x), r);
      }

      auto notdone = is_gez(x) && !(iseqzn || iseq1n) ;
      x = if_else(notdone, x, allbits);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_half,  notdone, n == T(0.5), r, x);
        if( eve::any(notdone) )
        {
          if( eve::any(notdone) )
          {
            notdone = last_interval(br_medium,  notdone, r, n, x);
          }
        }
      }
      return r;
    }
  }
}
