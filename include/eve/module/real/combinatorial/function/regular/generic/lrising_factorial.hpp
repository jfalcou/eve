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
#include <eve/function/tgamma.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/constant/half.hpp>
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
                                         , T n,  T x, std::false_type const & ) noexcept
  {
    std::cout << "TODO" << std::endl;
    return nan(as(n+x));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , T n,  T x, std::true_type const & ) noexcept
  {
    auto absx = eve::abs(x);
    auto notdone = true_(as(x));
    auto r = zero(as(x));
    auto lp0 = [](auto n,  auto x)
      {
        std::cout << "lp0 "<< " x " << x << " n " << n << std::endl;
        return lgamma(x+n)-lgamma(n);
      };

    auto lp1 = [](auto n,  auto x)
      {
        std::cout << "lp1 "<< " x " << x << " n " << n << std::endl;
        const auto xovern = x/n;
        const auto den = inc(xovern);
        const auto d3 = den*den*den;
        const auto d5 = d3*den*den;
        const auto d7 = d5*den*den;
        const auto c1 = -xovern/den;
        const auto c3 = -xovern*(3.0+xovern*(3.0+xovern))/d3;
        const auto c5 = -xovern*(5.0+xovern*(10.0+xovern*(10.0+xovern*(5.0+xovern))))/d5;
        const auto c7 = -xovern*(7.0+xovern*(21.0+xovern*(35.0+xovern*(35.0+xovern*(21.0+xovern*(7.0+xovern))))))/d7;
        const auto p8 = eve::pow(inc(xovern),8);
        const auto c8 = dec(rec(p8));  /* these need not   */
        const auto c9 = dec(rec(p8*inc(xovern)));  /* be very accurate */
        const auto n2 = sqr(n);
        const auto n4 = sqr(n2);
        const auto n6 = n4*n2;
        const auto ser_1 = c1 + c3/(30*n2) + c5/(105*n4) + c7/(140*n6);
        const auto ser_2 = c8/(99*n6*n2) - 691*c9/(n6*n4)/360360;
        const auto ser = (ser_1 + ser_2)/ (12*n);

        auto term1 = x * dec(eve::log(n)); //eve::log(a/M_E);
        auto lg = eve::log1p(xovern);  /* log(1 + x/n) */
        auto term2 = (x + n - half(as(x))) * lg;

        return term1 + term2 + ser;
      };

    auto lp2 = [](auto n,  auto x)
      {
        std::cout << "lp2 "<< " x " << x << " n " << n << std::endl;
        return lrising_factorial(n, x, std::false_type());
      };

    if( eve::any(notdone) )
    {
      auto test0 = (10*absx > n) || (10*absx*log(eve::max(n, T(2))) > one(as(x)));
      std::cout << "---x " << x << std::endl;
      notdone = next_interval(lp0,  notdone, test0, r, x, n);
      if( eve::any(notdone) )
      {
        auto test1 =  (10*absx <= n) && (n > T(15));
        notdone = next_interval(lp1,  notdone, test1, r, x, n);
        if( eve::any(notdone) )
        {
          notdone = last_interval(lp2,  notdone, r, x, n);
        }
      }
    }
    std::cout << "r " << r << std::endl;
    return r;
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                        , T x, T n) noexcept
  {
    std::cout << "entre x " << x <<  "  n " << n << std::endl;
    if constexpr(has_native_abi_v<T>)
    {
      auto nnez =  is_nez(n);
      //   auto xnez =  is_nez(x);
      auto r = if_else(nnez, nan(as(x)), minf(as(x)));
      auto notdone = is_not_nan(x) || nnez;

      auto lpos = [](auto n,  auto x)
        {
          std::cout << "lpos" << std::endl;
          return lrising_factorial(n, x, std::true_type());
        };
      auto lr2 = [](auto n,  auto x)
        {
          std::cout << "lr2" << std::endl;
          /* Handle the case where both a and a+x are negative integers. */
          /* Use the reflection formula AMS6.1.17
             poch(-a,-x) = (-1)^x (a/(a+x)) 1/poch(a,x) */
          auto r = lrising_factorial(-n, -x, std::true_type());
          auto f = -eve::log1p(x/n);
          return f - r;
        };
      auto lr3 = [](auto n,  auto)
        {
           std::cout << "lr3" << std::endl;
         /* Handle a+x = 0 i.e. Gamma(0)/Gamma(a) */
          /* poch (-a,a) == (-1)^a Gamma(a+1) */
           return lgamma(inc(n));
        };
      auto lr4 = [](auto n,  auto )
        {
          std::cout << "lr4" << std::endl;
          //a < 0.0 && a+x < 0.0
          /* Handle finite numerator, Gamma(a+x) for a+x != 0 or neg int */
          return minf(as(n));
        };

      auto lr5 = [](auto n ,  auto x)
        {
          std::cout << "lr5" << std::endl;
          // Reduce to positive case using reflection.
          auto omn = oneminus(n);
          auto sin_1 = sinpi(omn);
          auto sin_2 = sinpi(omn-x);
          //    if(sin_1 == 0.0 || sin_2 == 0.0) return nan
          auto r = lrising_factorial(omn, -x, std::true_type());
          auto lnterm = eve::log(eve::abs(sin_1/sin_2));
          return lnterm - r;
          //      *sgn = GSL_SIGN(sin_1*sin_2);
        };

      auto lr6 = [](auto n,  auto x)
        {
          std::cout << "lr6" << std::endl;
          std::cout << "x " << x <<  "  n " << n << std::endl;
          std::cout << "res " << eve::lgamma(n+x)-eve::lgamma(n)<< std::endl;
          //          return eve::lgamma(n+x)-eve::lgamma(n);
          std::cout << "eve::lgamma(n+x) " << eve::lgamma(n+x)<< std::endl;
          std::cout << "eve::lgamma(n)   " << eve::lgamma(n  )<< std::endl;
          std::cout << "log(eve::abs(tgamma(n+x)) " << log(eve::abs(tgamma(n+x))) << std::endl;
          std::cout << "log(eve::abs(tgamma(n)) " << log(eve::abs(tgamma(n))) << std::endl;
          return eve::log(eve::abs(tgamma(n+x))-eve::log(eve::abs(tgamma(n))));
          //   return eve::lgamma(n+x)-eve::lgamma(n);
        };

      if( eve::any(notdone) )
      {
        auto ispos = is_gtz(n) && is_gtz(n+x);
        notdone = next_interval(lpos,  notdone, ispos, r, x, n);
        if( eve::any(notdone) )
        {
          auto testz = is_lez(n) && (eve::floor(n) == n);
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
                notdone = last_interval(lr6, notdone, r, x, n);
              }
            }
          }
        }
      }
      return if_else(is_nez(n), r, minf(as(x)));
    }
    else
      return apply_over(lrising_factorial, n, x);
  }
}
