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
#include <eve/function/pedantic.hpp>
#include <eve/function/derivative.hpp>
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
  //general case
  template<real_value I, floating_real_value T, decorator D>
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

  // regular wrapping : no decorator
  template<real_value I,floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , I a,  T x) noexcept
  {
    return lrising_factorial(regular_type(), a, x);
  }

  // regular  nan if a+x or x is nnegative,  better computation than raw
  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , regular_type const &
                                         , T a,  T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
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
      auto notdone = is_nltz(x) || is_nltz(a+x);
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
    else
      return apply_over(regular(lrising_factorial), a, x);
  }

  // raw direct computation not matter why. nan if a+x or x is non positive
  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , raw_type const &
                                         , T a,  T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto notdone = is_nlez(x) && is_nlez(a+x);
      return if_else(notdone, lgamma(x+a)-lgamma(a), allbits);
    }
    else
      return apply_over(raw(lrising_factorial), a, x);
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
        return lgamma(x+a)-lgamma(a);
      };

    auto lr1 = [](auto a,  auto x)
      {
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
       return  if_else(dist(x+a, a) < 10*a*eps(as(a)) , eve::log1p(x*digamma(a)), lgamma(a+x)-lgamma(a));
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
    return r;
  }
}
