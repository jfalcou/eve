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
#include <eve/module/math.hpp>

namespace eve::detail
{
  template<typename T, callable_options O> constexpr
  T airy_bi_(EVE_REQUIRES(cpu_), O const&, T x)
  {
    using elt_t   = element_type_t<T>;
    auto ax       = eve::abs(x);
    T    rac      = eve::sqrt(ax);
    T    racthird = rac * T(0.577350269189626);
    T    p        = (ax * rac * 2) / 3;
    T    v        = T(1.0 / 3);

    auto br_0     = [v, p, racthird]()
    {
      T j1 = bessel_j(v, p);
      T j2 = bessel_j(-v, p);
      return racthird * (j2 - j1);
    };
    auto br_small = []() { return T(0.614926627446001); };
    auto br_last  = [v, p, racthird]()
    {
      T j1 = bessel_i(v, p);
      T j2 = bessel_i(-v, p);
      return racthird * (j1 + j2);
    };
    elt_t constexpr thresh = (sizeof(elt_t) == 8) ? (4.440892098500626e-16) : (2.3841858e-07);

    if constexpr( scalar_value<T> )
    {
      if( x == minf(as(x)) )  return zero(as(x));
      if( is_nan(x) )         return nan(as(x));
      if( x == inf(as(x)) )   return inf(as(x));
      if( x < 0 )             return br_0();
      if( x < thresh )        return br_small();
      return br_last();
    }
    else
    {
      auto r       = nan(as(x));
      auto notdone = (x != minf(as(x)) && is_not_nan(x));
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_0, notdone, is_ltz(x), r);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_small, notdone, x < thresh, r);
          if( eve::any(notdone) ) { last_interval(br_last, notdone, r); }
        }
      }
      r = if_else(x == inf(as(x)), inf(as(x)), r);
      r = if_else(x == minf(as(x)), zero, r);
      return r;
    }
  }
}
