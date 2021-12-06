//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/cyl_bessel_jn.hpp>
#include <eve/function/cyl_bessel_kn.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/select_over.hpp>

namespace eve::detail
{
 template<floating_real_value T>
  EVE_FORCEINLINE auto airy_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    using elt_t =  element_type_t<T>;
    auto ax = eve::abs(x);
    T rac = eve::sqrt(ax);
    T racthird = rac*T(0.577350269189626);
    T p = (ax * rac * 2) / 3;
    T v = T(0.3333333333333333);
    auto br_0 = [v, p, rac, racthird]() {
      T j1 = cyl_bessel_jn(v, p);
      T j2 = cyl_bessel_jn(-v, p);
      return kumi::tuple<T, T>{rac*(j1 + j2) / 3, racthird * (j2 - j1)};
    };
    auto br_small = []() {
      return kumi::tuple<T, T>{T(0.355028053887817), T(0.614926627446001)};
    };
    auto br_last = [v, p, rac, racthird]() {
      T j1 = cyl_bessel_in(v, p);
      T j2 = cyl_bessel_in(-v, p);
      auto bi = racthird * (j1 + j2);
      auto ai = cyl_bessel_kn(v, p) * rac* T(0.183776298473931);// third *invpi(as(p));
      return kumi::tuple<T, T>{ai, bi};
    };
    elt_t constexpr thresh = (sizeof(elt_t) == 8) ? (4.440892098500626e-16) : (2.3841858e-07);
    if constexpr(scalar_value<T>)
    {
      if(x == minf(as(x))) return kumi::tuple<T, T>{zero(as(x)), zero(as(x))};
      if(is_nan(x))        return kumi::tuple<T, T>{nan(as(x)), nan(as(x))};
      if(x == inf(as(x)))  return kumi::tuple<T, T>{zero(as(x)), inf(as(x))};
      if(x < 0) return br_0();
      if(x < thresh) return br_small();
      return br_last();
    }
    else
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto r = kumi::tuple<T, T>{nan(as(x)), nan(as(x))};
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
        auto my_if_else =  []<typename A>(auto cond, A a,  auto b){
          if constexpr(kumi::product_type<A>)
          {
            auto f = [&cond](auto x, auto y){return eve::if_else(cond, x, y); };
            return kumi::map(f, a, b);
          }
          else
            return eve::if_else(cond, a, b);
        };
        r = select_over(is_infinite(x), kumi::tuple<T, T>{zero(as(x)), inf(as(x))}, r);
        get<0>(r) = if_else (x == minf(as(x)), zero, get<0>(r));
        return r;
      }
      else
        return apply_over2(airy, x);
    }
  }
}
