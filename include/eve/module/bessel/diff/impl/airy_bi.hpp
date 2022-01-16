//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/derivative.hpp

#include <eve/module/math.hpp>
#include <eve/module/bessel/regular/cyl_bessel_jn.hpp>
#include <eve/module/bessel/regular/cyl_bessel_in.hpp>
#include <eve/detail/hz_device.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T airy_bi_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    using elt_t =  element_type_t<T>;
    auto ax = eve::abs(x);
    T rac = eve::sqrt(ax);
    T p = (ax * rac * 2) / 3;
    T v = T(0.6666666666666666);
    auto br_0 = [v, p, ax]() {
      T j1 = cyl_bessel_jn(v, p);
      T j2 = cyl_bessel_jn(-v, p);
      return ax*(j1 + j2) * T(0.577350269189626);
    };
    auto br_small = []() {
      return T(0.448288357353826);
    };
    auto br_last = [v, p, x]() {
      T i1 = cyl_bessel_in(-v, p);
      T i2 = cyl_bessel_in(v, p);
      return x * (i1 + i2) * T(0.577350269189626);
    };
    elt_t constexpr thresh = (sizeof(elt_t) == 8) ? (2.107342425544702e-08) : (4.8828125e-04);//sqrt(2*eps)
    if constexpr(scalar_value<T>)
    {
      if(x == minf(as(x))) return zero(as(x));
      if(is_nan(x))        return nan(as(x));
      if(x == inf(as(x)))  return inf(as(x));
      if(x < 0) return br_0();
      if(x < thresh) return br_small();
      return br_last();
    }
    else
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto r = nan(as(x));
        auto notdone = is_not_nan(x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_0,  notdone, is_ltz(x), r);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_small,  notdone, x < thresh, r);
            if( eve::any(notdone) )
            {
              last_interval(br_last,  notdone, r);
            }
          }
        }
        r = if_else (x == inf(as(x)), x, r);
        r = if_else (x ==minf(as(x)), zero, r);
        return r;
      }
      else
        return apply_over(diff(airy_bi), x);
    }
  }
}
