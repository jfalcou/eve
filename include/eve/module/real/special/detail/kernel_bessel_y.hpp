//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/function/cyl_bessel_j1.hpp>
#include <eve/function/cyl_bessel_y0.hpp>
#include <eve/function/cyl_bessel_y1.hpp>
#include <eve/function/digamma.hpp>
#include <eve/function/factorial.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/log.hpp>
#include <eve/function/maximum.hpp>
#include <eve/function/nthroot.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sinpicospi.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/function/converter.hpp>
#include <eve/module/real/special/detail/kernel_bessel_jy_large.hpp>
#include <eve/module/real/special/detail/kernel_bessel_jy_small.hpp>
#include <eve/module/real/special/detail/kernel_bessel_jy.hpp>

/////////////////////////////////////////////////////////////////////////////////
// These routines are detail of the computation of cylindrical bessel functions
// of the second kind and integer orders.
// They are not meant to be called directly,  as their validities depends on
// n and x ranges values which are not tested on entry.
// The inspiration is from boost math
/////////////////////////////////////////////////////////////////////////////////
namespace eve::detail
{

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_y_large (I n, T x) noexcept
  {
    return asymptotic_bessel_y_large_x_2(T(n), x);
  }

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_y_int_forward (I n, T x, T y0, T y1) noexcept
  {
    auto prev = y0; //cyl_bessel_y0(x);
    auto current = y1; //cyl_bessel_y1(x);
    int k = 1;
    EVE_ASSERT(eve::all(k+1 < n), "some ns are less than 2");
    T factor(1);
    T mult = 2 * k / x;
    auto  value = fms(mult, current, prev);
    prev = current;
    current = value;
    ++k;
    auto test = (mult > 1) && (eve::abs(current) > 1);
    if(eve::any(test))
    {
      prev  = if_else(test, prev/current,  prev);
      factor = if_else(test, factor/current, factor);
      value  = if_else(test, value/current,  value);
      current = if_else(test, one, current);
    }
    auto const maxn = maximum(n);
    while(k < maxn)
    {
      auto t0 = k < n;
      mult = if_else(t0, 2 * k / x, zero);
      value =if_else(t0, fms(mult, current, prev), value);
      prev  = current;
      current = value;
      ++k;
    }
    return value /factor;
  }

  template<integral_real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_y_int_forward (I nn, T x, T y0, T y1) noexcept
  {
    if constexpr(simd_value<I>)
      return kernel_bessel_y_int_forward (convert(nn, as<element_type_t<T>>()), x, y0, y1);
    else
      return kernel_bessel_y_int_forward (T(nn), x, y0, y1);
  }

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_y_int_small (I , T x) noexcept
  {
    return x; //bessel_y_small_z_series(T(n), x);
  }

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_y_medium (I n, T x) noexcept
  {
    auto [j, jp, y, yp] = bessel_jy(T(n), x);
    return y;
  }

  template <floating_real_value T>
  auto kernel_bessel_Yn_small_x(T n, T x)
  {
//     std::cout << "x " << x << std::endl;
//     std::cout << "n " << n << std::endl;
//     std::cout << "kernel_bessel_Yn_small_x" << std::endl;
    auto xlt5 = x < T(5);
    x = if_else(xlt5, x, one);
    n = if_else(xlt5, n, one);
//     std::cout << "x " << x << std::endl;
//     std::cout << "n " << n << std::endl;
    using elt_t = element_type_t<T>;
    T y = elt_t(0.25) * sqr(x);
    T ln_x_2 = eve::log(elt_t(0.5)*x);
    T ln_nm1_fact = eve::lgamma(n);
    //   gsl_sf_lnfact_e((unsigned int)(n-1), &ln_nm1_fact);

    T ln_pre1 = -n*ln_x_2 + ln_nm1_fact;

//    if(ln_pre1 > GSL_LOG_DBL_MAX - 3.0) GSL_ERROR ("error", GSL_EOVRFLW);

    T sum1(1);
    T k_term(1);

    for(int k=1; k < maximum(n); ++k) {
      auto kltn = k < n;
      k_term = if_else(kltn, k_term*(y/(k * (n-k))), k_term);
      sum1   += if_else(kltn, k_term, zero);
    }
    T term1 = -eve::exp(ln_pre1) * sum1 *invpi(as(x));

    T pre2 = -exp(n*ln_x_2) *invpi(as(x));
    T term2(0);
    if(eve::all(eve::abs(pre2) > 0.0))
    {
     constexpr int KMAX = 20;
      T psi_n = digamma(n);
      T npk_fact = tgamma(inc(n)); //eve::factorial(n);
      T yk(1);
      T k_fact(1);
      T psi_kp1 = T(-0.57721566490153286060651209008240243104215933593992);
      T psi_npkp1 = psi_n + rec(n);
      T sum2 = (psi_kp1 + psi_npkp1 - 2.0*ln_x_2)/npk_fact;
      for(elt_t k=1; k<KMAX; k = inc(k))
      {
        psi_kp1   += rec(k);
        psi_npkp1 += rec(n+k);
        k_fact   *= k;
        npk_fact *= n+k;
        yk *= -y;
        k_term = yk*(psi_kp1 + psi_npkp1 - 2*ln_x_2)/(k_fact*npk_fact);
        sum2 += k_term;
      }
      term2 = pre2 * sum2;
    }
    return term1+term2;
  }

  /////////////////////////////////////////////////////////////////////////
  // bessel_y of integer order
  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_y_int (I n, T x) noexcept
  {
    // n < abs(z), forward recurrence stable and usable
    // n >= abs(z), forward recurrence unstable, use Miller's algorithm
    EVE_ASSERT(eve::all(is_flint(n)), "kernel_bessel_y_int : somme n are not floating integer");

    auto br_large =  [](auto n,  auto x)
      {
//        std::cout << "br_large" << std::endl;
        return kernel_bessel_y_large(n, x);
      };
    auto br_forward =  [](auto n,  auto x)
      {
 //        std::cout << "br_forward" << std::endl;
        auto y0 = cyl_bessel_y0(x);
        auto y1 = cyl_bessel_y1(x);
        auto z =  kernel_bessel_y_int_forward (n, x, y0, y1);
        z = if_else(is_eqz(n), y0, z);
        return if_else(n == one(as(n)), y1, z);
      };
    auto br_small =  [](auto n,  auto x)
      {
 //        std::cout << "br_small x = " << x << ", n = "<< n << std::endl;
        return kernel_bessel_Yn_small_x(n, x);
      };
    auto br_medium =  [](auto n,  auto x)
      {
 //        std::cout << "br_medium" << std::endl;
        return kernel_bessel_y_medium (n, x);
      };

    if constexpr(scalar_value<I> && scalar_value<T>)
    {
      T factor(1);
      auto isoddn = is_odd(n);
      if (n < 0)
      {
        factor = T(isoddn ? -1 : 1);  // J_{-n}(z) = (-1)^n J_n(z)
        n = -n;
      }
      if (is_ngez(x))                              return nan(as(x));
      if (is_eqz(x))                                return minf(as(x));
      if (x == inf(as(x)))                          return zero(as(x));
      if (asymptotic_bessel_large_x_limit(T(n), x)) return factor*br_large(T(n), x);
      if (n == 0)                                   return cyl_bessel_y0(x);      //cyl_bessel_y0(x);
      if (n == 1)                                   return factor*cyl_bessel_y1(x);      //cyl_bessel_y1(x);
      if (n < eve::abs(x))                          return factor*br_forward(n, x);      // forward recurrence
      if (/*(n > x * x / 4) ||*/ (x < 5))               return factor*br_small(T(n), x); // serie
      return br_medium(n, x);                                                     // medium recurrence
    }
    else
    {
      using elt_t =  element_type_t<T>;
      T factor(1);
      auto isoddn = is_odd(n);
      auto nneg = is_ltz(n);
      factor = if_else(nneg, if_else(isoddn, T(-1), T(1)), factor);  // J_{-n}(z) = (-1)^n J_n(z)
      n = if_else(nneg, -n, n);

      auto r = nan(as(x));
      auto isinfx = x == inf(as(x));
      r =  if_else(isinfx, zero(as(x)), allbits);
      x = if_else(isinfx, mone, x);
//       auto iseqzn = is_eqz(n);
//       if (eve::any(iseqzn))
//       {
//         auto y0 = cyl_bessel_y0(x);
//         r = if_else(iseqzn, y0, r);
// //        x = if_else(iseqzn, allbits, x);
//       }
//       auto iseq1n = is_equal(n, one(as(n)));
//       if (eve::any(iseq1n))
//       {
//         auto y1 = cyl_bessel_y1(x);
//         r = if_else(iseq1n, y1, r);
// //        x = if_else(iseq1n, allbits, x);
//       }
      auto iseqzx = is_eqz(x);
      if (eve::any(iseqzx))
      {
        r = if_else(iseqzx, minf(as(x)), r);
//        x = if_else(iseqzx, allbits, x);
      }

      auto notdone = is_nltz(x);
//       std::cout << std::setprecision(10) << "x       " << x << std::endl;
//       std::cout << "r       " << r << std::endl;
//      std::cout << "notdone " << notdone << std::endl;
      x = if_else(notdone, x, allbits);
      auto nn = convert(n, as<elt_t>());
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_large,  notdone, asymptotic_bessel_large_x_limit(nn, x), r, nn, x);
//      std::cout << "notdone 1" << notdone << std::endl;
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_forward,  notdone, nn < x, r, nn, x);
//       std::cout << "notdone 2" << notdone << std::endl;
         if( eve::any(notdone) )
          {
            notdone = next_interval(br_small,  notdone, /*(nn > x * x / 4) ||*/ (x < 5), r, nn, x);
//       std::cout << "notdone 3" << notdone << std::endl;
           if( eve::any(notdone) )
            {
              notdone = last_interval(br_medium,  notdone, r, nn, x);
//       std::cout << "notdone 4" << notdone << std::endl;
           }
          }
        }
      }
      return factor*r;
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto  kernel_bessel_y_flt (T n, T x) noexcept
  {
    EVE_ASSERT(eve::none(is_flint(n)), "kernel_bessel_y_flt : some nu are floating integers");
    auto br_large =  [](auto n,  auto x)
      {
        return kernel_bessel_y_large(n, x);
      };

    auto br_medium =  [](auto n,  auto x)
      {
        return  kernel_bessel_y_medium(n, x);
      };

    if constexpr(scalar_value<T>)
    {
      if (is_ltz(x)||is_ltz(n))                     return nan(as(x));
      if (is_eqz(x))                                return minf(as(x));
      if (x == inf(as(x)))                          return zero(as(x));
      if (asymptotic_bessel_large_x_limit(n, x))    return br_large(n, x);
      return br_medium(n, x);
    }
    else
    {
      auto r = nan(as(x));
      auto isinfx = x == inf(as(x));
      r = if_else(isinfx, zero(as(x)), allbits);
      x = if_else(isinfx, mone, x);
      auto notdone = is_nltz(x);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_large,  notdone, asymptotic_bessel_large_x_limit(n, x), r, n, x);
        if( eve::any(notdone) )
        {
          notdone = last_interval(br_medium,  notdone, r, n, x);
        }
      }
      return r;
    }
  }

}
