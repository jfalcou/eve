//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/atan.hpp>
#include <eve/function/log.hpp>
#include <eve/function/atanh.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/max.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/sub.hpp>
#include <eve/detail/hz_device.hpp>


namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto ellint_rc_(EVE_SUPPORTS(cpu_)
                              , T x
                              , U y) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(ellint_rc, x, y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_rc_(EVE_SUPPORTS(cpu_)
                              , T x
                              , T y) noexcept
  requires has_native_abi_v<T>
  {
    auto ylt0 = is_ltz(y);
    auto prefix = one(as(x));
    if (eve::any(ylt0)) //provisions for y < 0
    {
      prefix = if_else(ylt0, sqrt(x / (x - y)), one);
      x =  sub[ ylt0](x, y);
      y =  if_else( ylt0, -y, y);
    }
    // now all y are >= 0
    auto r =  nan(as(x));
    auto notdone = is_nltz(x) && is_nez(y);
    if (eve::any(notdone))
    {
      auto tmp0 = rsqrt(y);
      auto br_0 =  [tmp0](auto x,  auto y) // x == y || x == 0
        {
          auto z = mul[is_eqz(x)](tmp0, pio_2(as(y)));
          return z;  //if_else(x == y, tmp0, tmp0*pio_2(as(y)));
        };
      notdone = next_interval(br_0, notdone, (x == y) || is_eqz(x), r, x, y);
      if  (eve::any(notdone))
      {
        auto tmp1 = sqrt(eve::abs(x - y));
        auto tmp2 = rsqrt(x);
        auto tmp3 = tmp1*tmp2;
        auto br_1 =  [tmp1, tmp3]() // y >  x
          {
            return atan(tmp3)/tmp1;
          };
        notdone = next_interval(br_1, notdone, y > x, r);
        if  (eve::any(notdone))
        {
          auto br_2 =  [tmp1, tmp3]() // y > 0.5*x
            {
              return atanh(tmp3)/tmp1;
            };
          notdone = next_interval(br_2, notdone, y > T(0.5)*x , r);
          if(eve::any(notdone))
          {
            auto br_3 = [tmp0, tmp1](auto x)
              {
                return log((sqrt(x) + tmp1)*tmp0)/tmp1;
              };
            last_interval(br_3, notdone, r, x);
          }
        }
      }
    }
    return if_else(x == inf(as(x)), zero, r*prefix);
  }
}
