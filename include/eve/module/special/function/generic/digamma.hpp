//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/epsilon.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/gammaln.hpp>
#include <eve/function/log.hpp>
#include <eve/function/max.hpp>
#include <eve/function/maximum.hpp>
#include <eve/function/min.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T gammainc_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    auto dlarge = (std::is_same_v<elt_t>, double>, 20, 10);
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr(scalar_value<T>)
      {
        if (is_eqz(a0)) return copysign(inf(as(x)), x);
        if( x < 0)
        {
          x =  oneminus(x);
          auto r = x - floor(x);
          if (r > 0.5)  r -= 1;
          if (r == 0.5) r =  0;
          else if (r) r = pi(as(x))/tanpi(r);
          else r = nan(as(x));
          // we are ready to increment result that was
          // Pi/tanpi(r) if x < 0  and r != 0
          // nan         if x < 0  and r == 0
          // 0           in any other cases
        }
        if(x >= dlarge)
        { // If we're above the lower-limit for the asymptotic expansion then use it:
          return digamma_imp_large(x)+result;
        }
        // If x > 2 reduce to the interval [1,2]:
        while(x > 2)
        {
          x -= 1;
          r += rec(x);
        }
        // If x < 1 use shift to > 1:
        if(x < 1)
        {
          r = -rec(x);
          x += 1;
        }
        return digamma_1_2(x)+r;
      }
      else
      {
        auto result = zero(as(x));
        auto test = is_lez(a0);

        if(any(test))
        {
          auto a = x;
          x = oneminus[test](x);
          auto remainder = frac(x);
          remainder = sub[remainder > T(0.5)](one(as(x)));
          remainder = if_else(is_eqz(remainder), nan(as(x)), remainder);
          remainder = if_else(remainder == T(0.5), zero, pi(as(x))*cotpi(remainder));
          result = if_else(is_eqz(a), copysign(inf(as(x)), a), remainder);
          result = if_else(test, result, zero);
        }
        auto r1 = zero(as(x));
        auto br_large = [](auto x, auto result){
          //if we're above the lower-limit for the asymptotic expansion then use it:
          r1 = add[test](result, digamma_imp_large(x));
        };
        auto r = nan(as<T>()); //nan case treated here
        auto notdone =  is_not_nan(x);
        if(any(notdone))
        {
          notdone = next_interval(br_large,  notdone, x > dlarge, r, x, result);
          if(any(notdone))
          {
            // If x > 2 reduce to the interval [1,2]:
            x = if_else(x > dlarge, one, x);
            auto cond = x > 2;
            while(any(cond))
            {
              x =  dec[cond](x);
              result = add[cond](result,rec(x));
              cond = x > 2;
            }
            cond = x < 1;
            if(any(cond)) // back one step
            {
              result = seladd[cond] -rec(x), result);
              x =  inc[cond](x);
            }
            notdone = last_interval(digamma_1_2,  notdone, r, x);
            return r;
          }
        }
      }
    }
    else
      return apply_over(dawson, a0);
  }
}
