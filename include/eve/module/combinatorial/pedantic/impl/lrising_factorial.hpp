//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/digamma.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/dist.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_nlez.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/exp.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/common_compatible.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/module/combinatorial/detail/lrising_factorial.hpp>

namespace eve::detail
{
  // pedantic computes also for negative values and even negative integer values
  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , pedantic_type const &
                                         , T a,  T x) noexcept
  {
   if constexpr(has_native_abi_v<T>)
    {
      auto r = nan(as(a));
      auto notdone = is_not_nan(a)&&is_not_nan(x);

      auto lr0 = []()
        {
          return zero(as(T()));
        };

      auto lrpos = [](auto a, auto x)
        {
          return inner_lrising_factorial(a, x);
        };

      auto lrnegint = [](auto a,  auto x)
        // a and a+x are negative integers uses reflection.
        {
          auto r = inner_lrising_factorial(-a, -x);
          return -eve::log1p(x/a)-r;
        };

      auto lraeqmx = [](auto a,  auto )
        // a+x = 0
        {
         return lgamma(inc(a));
        };

      auto lraneqmx = [](auto a,  auto )
        //a < 0.0 && a+x < 0.0
       {
          return minf(as(a));
       };

      auto lrneg = [](auto a,  auto x)
        {
          // Reduce to positive case using reflection.
          auto oma = oneminus(a);
          auto spioma = sinpi(oma);
          auto spiomamx = sinpi(oma-x);
          auto r = inner_lrising_factorial(oma, -x);
          auto lnterm = eve::log(eve::abs(spioma/spiomamx));
          return if_else(is_nez(spiomamx*spioma), lnterm - r, allbits);
        };

      auto lrlast = [](auto a,  auto x)
        {
         return eve::lgamma(a+x)-eve::lgamma(a);
        };

      if( eve::any(notdone) )
      {
        notdone = next_interval(lr0,  notdone, is_eqz(x), r);
        if( eve::any(notdone) )
        {
          auto testpos = is_nlez(a) && is_nlez(a+x);
          notdone = next_interval(lrpos, notdone,  testpos, r, a, x);
          if( eve::any(notdone) )
          {
            // from here a+x <= 0 ||  x <= 0
            auto aneg = is_ltz(a);
            auto aflint = is_flint(a);
            auto testnegint = aflint && is_flint(a+x) && aneg && is_ltz(a+x) ;
            notdone = next_interval(lrnegint, notdone, testnegint, r, a, x);
            if( eve::any(notdone) )
            {
              notdone = next_interval(lraeqmx, notdone, is_eqz(a+x), r, a, x);
              if( eve::any(notdone) )
              {
                notdone = next_interval(lraneqmx, notdone, aflint && !is_eqz(a+x), r, a, x);
                if( eve::any(notdone) )
                {
                  notdone = next_interval(lrneg, notdone, aneg && is_ltz(a+x), r, a, x);
                  if( eve::any(notdone) )
                  {
                    notdone = last_interval(lrlast, notdone, r, a, x);
                  }
                }
              }
            }
          }
        }
      }
      return r;
    }
    else
      return apply_over(pedantic(lrising_factorial), a, x);
  }
}
