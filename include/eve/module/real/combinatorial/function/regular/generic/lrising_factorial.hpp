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

namespace eve::detail
{
  template<real_value I, floating_real_value T,  decorator D>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , D const & d
                                         , I n,  T x) noexcept
  {
    if constexpr(integral_simd_value<I>)
    {
      using elt_t = element_type_t<T>;
      using r_t = as_wide_t<elt_t, cardinal_t<I>>;
      auto nn = convert(n, as(elt_t()));
      return d(lrising_factorial)(nn, r_t(x));
    }
    else if  constexpr(integral_scalar_value<I>)
    {
      return d(lrising_factorial)(T(n), x);
    }
    else
    {
      using r_t = common_compatible_t<I, T>;
      return d(lrising_factorial)(r_t(n), r_t(x));
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , raw_type const &
                                         , T a,  T x) noexcept
  {
    auto lr0 = []()
      {
        return zero(as(T()));
      };
    auto lrpos = [](auto a, auto x)
      {
        return lrising_factorial(a, x, std::true_type());
      };

    auto r = nan(as(a));
    auto notdone = is_nltz(x) && is_nltz(a+x);
    if( eve::any(notdone) )
    {
      notdone = next_interval(lr0,  notdone, is_eqz(x), r);
      if( eve::any(notdone) )
      {
        notdone = last_interval(lrpos, notdone, r, a, x);
      }
    }
    return r;
  }

  template<real_value I, floating_real_value T,  decorator D>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , I a,  T x) noexcept
  {
    return regular(lrising_factorial)(a, x);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , T a,  T x, std::false_type const & ) noexcept
  {
    std::cout << "TODO" << std::endl;
    return nan(as(a+x));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , T a,  T x, std::true_type const & ) noexcept
  {
    // Assumes a>0 and a+x>0.
    auto ax = eve::abs(x);
    auto notdone = is_nlez(a) && is_nlez(a+x);
    auto r = nan(as(x));
    auto lr0 = [](auto a,  auto x)
      {
        std::cout << "lr0 "<< " x " << x << " a " << a << std::endl;
        return lgamma(x+a)-lgamma(a);
      };

    auto lr1 = [](auto a,  auto x)
      {
        std::cout << "lr1 "<< " x " << x << " a " << a << std::endl;
        const auto xoa = x/a;
        const auto den = inc(xoa);
        const auto d2 = sqr(den);
        const auto d3 = den*d2;
        const auto d5 = d3*d2;
        const auto d7 = d5*d2;
        const auto c1 = -xoa/den;
        const auto c3 = -xoa*(3+xoa*(3+xoa))/d3;
        const auto c5 = -xoa*(5+xoa*(10+xoa*(10+xoa*(5+xoa))))/d5;
        const auto c7 = -xoa*(7+xoa*(21+xoa*(35+xoa*(35+xoa*(21+xoa*(7+xoa))))))/d7;
        const auto p8 = eve::pow(inc(xoa),8);
        const auto c8 = dec(rec(p8));  /* these need not   */
        const auto c9 = dec(rec(p8*inc(xoa)));  /* be very accurate */
        const auto a2 = sqr(a);
        const auto a4 = sqr(a2);
        const auto a6 = a4*a2;
        const auto ser_1 = c1 + c3/(30*a2) + c5/(105*a4) + c7/(140*a6);
        const auto ser_2 = c8/(99*a6*a2) - 691*c9/(a6*a4)/360360;
        const auto ser = (ser_1 + ser_2)/ (12*a);
        auto term1 = x * dec(eve::log(a)); //eve::log(a/M_E);
        auto lg = eve::log1p(xoa);
        auto term2 = (x + a - half(as(x))) * lg;
        return term1 + term2 + ser;
      };

    auto lr2 = [](auto a,  auto x)
      {
        std::cout << "lr2 "<< " x " << x << " a " << a << std::endl;
        return lrising_factorial(a, x, std::false_type());
      };

    if( eve::any(notdone) )
    {
      auto test0 = (10*ax > a) || (10*ax*log(eve::max(a, T(2))) > one(as(x)));
      notdone = next_interval(lr0,  notdone, test0, r, a, x);
      if( eve::any(notdone) )
      {
        auto test1 =  (10*ax <= a) && (a > T(15));
        notdone = next_interval(lr1,  notdone, test1, r, a, x);
        if( eve::any(notdone) )
        {
          notdone = last_interval(lr2,  notdone, r, a, x);
        }
      }
    }
    std::cout << "r " << r << std::endl;
    return r;
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                        , T a, T x) noexcept
  {
     if constexpr(has_native_abi_v<T>)
     {
       return a+x;
//     std::cout << "entre x " << x <<  "  n " << n << std::endl;
//     if constexpr(has_native_abi_v<T>)
//     {
//       auto nnez =  is_nez(n);
//       //   auto xnez =  is_nez(x);
//       auto r = if_else(nnez, nan(as(x)), minf(as(x)));
//       auto notdone = is_not_nan(x) || nnez;

//       auto lpos = [](auto n,  auto x)
//         {
//           std::cout << "lpos" << std::endl;
//           return lrising_factorial(n, x, std::true_type());
//         };
//       auto lr2 = [](auto n,  auto x)
//         {
//           std::cout << "lr2" << std::endl;
//           /* Handle the case where both a and a+x are negative integers. */
//           /* Use the reflection formula AMS6.1.17
//              poch(-a,-x) = (-1)^x (a/(a+x)) 1/poch(a,x) */
//           auto r = lrising_factorial(-n, -x, std::true_type());
//           auto f = -eve::log1p(x/n);
//           return f - r;
//         };
//       auto lr3 = [](auto n,  auto)
//         {
//            std::cout << "lr3" << std::endl;
//          /* Handle a+x = 0 i.e. Gamma(0)/Gamma(a) */
//           /* poch (-a,a) == (-1)^a Gamma(a+1) */
//            return lgamma(inc(n));
//         };
//       auto lr4 = [](auto n,  auto )
//         {
//           std::cout << "lr4" << std::endl;
//           //a < 0.0 && a+x < 0.0
//           /* Handle finite numerator, Gamma(a+x) for a+x != 0 or neg int */
//           return minf(as(n));
//         };

//       auto lr5 = [](auto n ,  auto x)
//         {
//           std::cout << "lr5" << std::endl;
//           // Reduce to positive case using reflection.
//           auto omn = oneminus(n);
//           auto sin_1 = sinpi(omn);
//           auto sin_2 = sinpi(omn-x);
//           //    if(sin_1 == 0.0 || sin_2 == 0.0) return nan
//           auto r = lrising_factorial(omn, -x, std::true_type());
//           auto lnterm = eve::log(eve::abs(sin_1/sin_2));
//           return lnterm - r;
//           //      *sgn = GSL_SIGN(sin_1*sin_2);
//         };

//       auto lr6 = [](auto n,  auto x)
//         {
//           std::cout << "lr6" << std::endl;
//           std::cout << "x " << x <<  "  n " << n << std::endl;
//           std::cout << "res " << eve::lgamma(n+x)-eve::lgamma(n)<< std::endl;
//           //          return eve::lgamma(n+x)-eve::lgamma(n);
//           std::cout << "eve::lgamma(n+x) " << eve::lgamma(n+x)<< std::endl;
//           std::cout << "eve::lgamma(n)   " << eve::lgamma(n  )<< std::endl;
//           std::cout << "log(eve::abs(tgamma(n+x)) " << log(eve::abs(tgamma(n+x))) << std::endl;
//           std::cout << "log(eve::abs(tgamma(n)) " << log(eve::abs(tgamma(n))) << std::endl;
//           return eve::log(eve::abs(tgamma(n+x))-eve::log(eve::abs(tgamma(n))));
//           //   return eve::lgamma(n+x)-eve::lgamma(n);
//         };

//       if( eve::any(notdone) )
//       {
//         auto ispos = is_gtz(n) && is_gtz(n+x);
//         notdone = next_interval(lpos,  notdone, ispos, r, x, n);
//         if( eve::any(notdone) )
//         {
//           auto testz = is_lez(n) && (eve::floor(n) == n);
//           auto xltz = is_ltz(x);
//           notdone = next_interval(lr2, notdone, testz && xltz, r, x, n);
//           if( eve::any(notdone) )
//           {
//             notdone = next_interval(lr3, notdone, testz && is_eqz(n+x), r, x, n);
//             if( eve::any(notdone) )
//             {
//               notdone = next_interval(lr4, notdone, testz && xltz, r, x, n);
//               auto testz1 = xltz && is_ltz(n+x);
//               if( eve::any(notdone) )
//               {
//                 notdone = next_interval(lr5, notdone, testz && testz1, r, x, n);//(n < 0.0 && n+x < 0.0)
//               }
//               if( eve::any(notdone) )
//               {
//                 notdone = last_interval(lr6, notdone, r, x, n);
//               }
//             }
//           }
//         }
//       }
//       return if_else(is_nez(n), r, minf(as(x)));
    }
    else
      return apply_over(lrising_factorial, a, x);
  }
}
