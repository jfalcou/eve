//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/lambert.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto omega_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto br_pos = [](auto x) {
        auto x0 = if_else(x > 1, x, -eve::log(eve::abs(x))+eps(as(x)));
        x0 =  if_else(is_nan(x), x, x0);
        int maxiter = 100;
        for(int i = 0;  i <= maxiter; ++i)
        {
          auto dx0 = x0*(log(x0)+x0-x)/inc(x0);
          auto test = is_not_greater(eve::abs(dx0), 2*eps(as(x))*eve::max(x, one(as(x))));
          if (eve::all(test)) break;
          x0 = eve::max(eve::smallestposval(as(x0)), x0-if_else(test, zero, dx0));
        }
        return x0;
      };
      auto br_neg = [](auto x) {
       auto [w0, wm1] = lambert(exp(x));
       return w0;
      };
      auto r = nan(as<T>());            //nan case treated here
      r = if_else(x == one(as(x)), one, r);
      r = if_else(x == inf(as(x)), inf(as(x)), r);
      r = if_else(x == zero(as(x)), T(0.56714329040978384011), r);
      auto notdone =  is_nan(r);
      if(eve::any(notdone))
      {
        notdone = next_interval(br_pos, notdone, x >= one(as(x)), r, x);
        if(eve::any(notdone))
        {
          notdone = last_interval(br_neg, notdone, r, x);
        }
      }
      return  r;
    }
    else
      return apply_over(omega, x);
  }
}
