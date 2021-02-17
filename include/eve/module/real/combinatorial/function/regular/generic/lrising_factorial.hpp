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

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/log.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/exp.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/common_compatible.hpp>
#include <eve/detail/hz_device.hpp>

namespace eve::detail
{
  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                        , I n,  T x) noexcept
  {
    if constexpr(integral_simd_value<I>)
    {
      using elt_t = element_type_t<T>;
      using r_t = as_wide_t<elt_t, cardinal_t<I>>;
      auto nn = convert(n, as(elt_t()));
      return lrising_factorial(nn, r_t(x));
    }
    else if  constexpr(integral_scalar_value<I>)
    {
      return lrising_factorial(T(n), x);
    }
    else
    {
      using r_t = common_compatible_t<I, T>;
      return lrising_factorial(r_t(n), r_t(x));
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                        , T n,  T x) noexcept
  {
     if constexpr(has_native_abi_v<T>)
     {
       auto xnez =  is_nez(x);
       auto r = if_else(xnez, nan(as(x)), zero);
       auto notdone = is_not_nan(x) || xnez;

       auto lpos = [](auto n,  auto x)
         {
           return n+x; //lrpos(n, x);
         };
        auto lr2 = [](auto n,  auto x)
         {
           /* Handle the case where both a and a+x are negative integers. */
           /* Use the reflection formula AMS6.1.17
              poch(-a,-x) = (-1)^x (a/(a+x)) 1/poch(a,x) */
           auto r = -n-x; //lrpos (-n, -x);
           auto f = log (n / (n + x));
           return f - r;
         };
        auto lr3 = [](auto n,  auto)
         {
           /* Handle a+x = 0 i.e. Gamma(0)/Gamma(a) */
           /* poch (-a,a) == (-1)^a Gamma(a+1) */
           return gamma(oneminus(n));
         };
        auto lr4 = [](auto n,  auto )
          {
            //a < 0.0 && a+x < 0.0
            /* Handle finite numerator, Gamma(a+x) for a+x != 0 or neg int */
            return minf(as(n));
          };

        auto lr5 = [](auto n ,  auto x)
          {
            /* Reduce to positive case using reflection.
             */
            auto omn = oneminus(n);
            auto sin_1 = sinpi(omn);
            auto sin_2 = sinpi(omn-x);
            //    if(sin_1 == 0.0 || sin_2 == 0.0) return nan
            auto r = omn-x; //lrpos(omn, -x);
            auto lnterm = eve::log(eve::abs(sin_1/sin_2));
            return lnterm - r;
            //      *sgn = GSL_SIGN(sin_1*sin_2);
          };

        auto lr6 = [](auto n ,  auto x)
          {
            return lgamma(n+x)-lgamma(n);
          };

        if( eve::any(notdone) )
        {
          auto ispos = is_gtz(n) && is_gtz(n+x);
          notdone = next_interval(lpos,  notdone, ispos, r, x, n);
          if( eve::any(notdone) )
          {
            auto testz = is_lez(n) && is_flint(n);
            auto xltz = is_ltz(x);
            notdone = next_interval(lr2, notdone, testz && xltz, r, x, n);
            if( eve::any(notdone) )
            {
              notdone = next_interval(lr3, notdone, testz && is_eqz(n+x), r, x, n);
              if( eve::any(notdone) )
              {
                notdone = next_interval(lr4, notdone, testz && xltz, r, x, n);
                auto testz1 = xltz && is_ltz(n+x);
                if( eve::any(notdone) )
                {
                  notdone = next_interval(lr5, notdone, testz && testz1, r, x, n);//(n < 0.0 && n+x < 0.0)
                }
                if( eve::any(notdone) )
                {
                  notdone = last_interval(lr6, notdone, r, x, n);//(n < 0.0 && n+x < 0.0)
                }
              }
            }
          }
        }
     }
    else
      return apply_over(lrising_factorial, n, x);
  }
}
