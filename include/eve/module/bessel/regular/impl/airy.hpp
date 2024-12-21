//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/bessel/regular/bessel_i.hpp>
#include <eve/module/bessel/regular/bessel_j.hpp>
#include <eve/module/bessel/regular/bessel_k.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
  template<typename T, typename O> constexpr
  kumi::tuple<T, T> airy_(EVE_REQUIRES(cpu_), O const&, T x)
  {
    using elt_t   = element_type_t<T>;
    auto ax       = eve::abs(x);
    T    rac      = eve::sqrt(ax);
    T    racthird = rac * T(0.577350269189626);
    T    p        = (ax * rac * 2) / 3;
    T    v        = T(1.0 / 3);
    auto br_0     = [v, p, rac, racthird]()
    {
      T j1 = bessel_j(v, p);
      T j2 = bessel_j(-v, p);
      return zip(rac * (j1 + j2) / 3, racthird * (j2 - j1));
    };

    auto br_small = []() { return eve::zip(T(0.355028053887817), T(0.614926627446001)); };
    auto br_last  = [v, p, rac, racthird]()
    {
      T    j1 = bessel_i(v, p);
      T    j2 = bessel_i(-v, p);
      auto bi = racthird * (j1 + j2);
      auto ai = bessel_k(v, p) * rac * T(0.183776298473931); // third *inv_pi(as(p));
      return zip(ai, bi);
    };

    elt_t constexpr thresh = (sizeof(elt_t) == 8) ? (4.440892098500626e-16) : (2.3841858e-07);
    if constexpr( scalar_value<T> )
    {
      if( x == minf(as(x)) )      return zip(zero(as(x)), zero(as(x)));
      else if( is_nan(x) )        return zip(nan(as(x)), nan(as(x)));
      else if( x == inf(as(x)) )  return zip(zero(as(x)), inf(as(x)));
      else if( x < 0 )            return br_0();
      else if( x < thresh )       return br_small();
      else                        return br_last();
    }
    else
    {
      auto r       = eve::zip(nan(as(x)), nan(as(x)));
      auto notdone = is_not_nan(x);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_0, notdone, is_ltz(x), r);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_small, notdone, x < thresh, r);
          if( eve::any(notdone) ) { last_interval(br_last, notdone, r); }
        }
      }
      r         = if_else(is_infinite(x), zip(zero(as(x)), inf(as(x))), r);
      get<0>(r) = if_else(x == minf(as(x)), zero, get<0>(r));
      return r;
    }
  }
}
