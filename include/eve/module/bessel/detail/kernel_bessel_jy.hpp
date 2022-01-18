//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/detail/kumi.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T>
  EVE_FORCEINLINE auto bessel_jy(T n, T x) noexcept
  {
    T nu(n);
    T jnu, jpnu, nnu, npnu;
    if (x == inf(as(x))) return kumi::make_tuple(T(0), nan(as(x)), T(0), nan(as(x)));
    else if (is_ltz(x)) return kumi::make_tuple(nan(as(x)),  nan(as(x)),  nan(as(x)), nan(as(x)));
    else if (is_eqz(x))
    {
      if (is_eqz(nu))
      {
        return kumi::make_tuple(T(1), T(0), minf(as(x)), inf(as(x))); //jnu, jpnu, nnu, npnu
      }
      else if (nu ==one(as(x)))
      {
        return kumi::make_tuple(T(0), T(0.5), minf(as(x)), inf(as(x))); //jnu, jpnu, nnu, npnu
      }
      else
      {
        return kumi::make_tuple(T(0), T(0), minf(as(x)), inf(as(x))); //jnu, jpnu, nnu, npnu
      }
    }

    auto reflect(is_ltz(nu));
    nu =  eve::abs(nu); // v is non-negative from here


    const T Eps = eve::eps(as(x));
    const T fp_min = eve::sqrt(smallestposval(as(x)));
    constexpr int max_iter = 15000;
    const T x_min = T(2);
    const int nl = (x < x_min ? static_cast<int>(nu + T(0.5)) : eve::max(0, static_cast<int>(nu - x + T(1.5))));
    const T mu = nu - nl;
    const T mu2 = sqr(mu);
    const T xi = rec(x);
    const T xi2 = xi + xi;
    T w = xi2 *invpi(as(x));
    int isign = 1;
    T h = nu * xi;
    if (h < fp_min)  h = fp_min;
    T b = xi2 * nu;
    T d = T(0);
    T c = h;
    {
      int i;
      for (i = 1; i <= max_iter; ++i)
      {
        b += xi2;
        d = b - d;
        if (eve::abs(d) < fp_min) d = fp_min;
        c = b - T(1) / c;
        if (eve::abs(c) < fp_min) c = fp_min;
        d = T(1) / d;
        const T del = c * d;
        h *= del;
        if (d < T(0))  isign = -isign;
        if (eve::abs(del - T(1)) < Eps) break;
      }
      if (i > max_iter) return kumi::make_tuple(nan(as(x)), nan(as(x)), nan(as(x)), nan(as(x)));
    }
    T jnul = isign * fp_min;
    T jpnul = h * jnul;
    T jnul1 = jnul;
    T jpnu1 = jpnul;
    T fact = nu * xi;
    for ( int l = nl; l >= 1; --l )
    {
      const T jnutemp = fma(fact, jnul, jpnul);
      fact -= xi;
      jpnul = fact * jnutemp - jnul;
      jnul = jnutemp;
    }
    if (jnul == T(0)) jnul = Eps;
    T f = jpnul / jnul;
    T nmu, nnu1, npmu, jmu;
    auto Pi = eve::pi(as(x));
    if (x < x_min)
    {
      const T x2 = x / T(2);
      T fact = rec(sinpic(mu));
      T d = -eve::log(x2);
      T e = mu * d;
      T fact2 = (eve::abs(e) < Eps ? T(1) : std::sinh(e) / e);
      T gam1, gam2, gampl, gammi;

      auto gamma_temme = [&gam1, &gam2, &gampl, &gammi, Eps](auto mu) {
        auto gamma_e = T(0.57721566490153286060651209008240243104215933593992);
        gampl = rec(tgamma(inc(mu)));
        gammi = rec(tgamma(oneminus(mu)));
        gam1 = eve::abs(mu) < Eps ? gamma_e : (gammi - gampl) /(mu+mu);
        gam2 = average(gammi, gampl);
        return;
      };

      gamma_temme(mu);
      T ff = (T(2) /Pi)
        * fact * (gam1 * eve::cosh(e) + gam2 * fact2 * d);
      e = eve::exp(e);
      T p = e / (Pi * gampl);
      T q = T(1) / (e *Pi * gammi);
      T muo2 = mu*T(0.5);
      T fact3 = sinpic(muo2);
      T r = sqr(Pi*fact3)*muo2;
      T c = T(1);
      d = -x2 * x2;
      T sum = ff + r * q;
      T sum1 = p;
      {
        int i;
        for (i = 1; i <= max_iter; ++i)
        {
          ff = (i * ff + p + q) / (i * i - mu2);
          c *= d / T(i);
          p /= T(i) - mu;
          q /= T(i) + mu;
          const T del = c * (ff + r * q);
          sum += del;
          const T del1 = c * p - i * del;
          sum1 += del1;
          if ( eve::abs(del) < Eps*(T(1) + eve::abs(sum)) )
            break;
        }
      }        nmu = -sum;
      nnu1 = -sum1 * xi2;
      npmu = mu * xi * nmu - nnu1;
      jmu = w / (npmu - f * nmu);
    }
    else
    {
      T a = T(0.25L) - mu2;
      T q = T(1);
      T p = -xi / T(2);
      T br = T(2) * x;
      T bi = T(2);
      T fact = a * xi / (p * p + q * q);
      T cr = br + q * fact;
      T ci = bi + p * fact;
      T den = br * br + bi * bi;
      T dr = br / den;
      T di = -bi / den;
      T dlr = cr * dr - ci * di;
      T dli = cr * di + ci * dr;
      T temp = p * dlr - q * dli;
      q = p * dli + q * dlr;
      p = temp;
      {
        int i;
        for (i = 2; i <= max_iter; ++i)
        {
          a += T(2 * (i - 1));
          bi += T(2);
          dr = a * dr + br;
          di = a * di + bi;
          if (eve::abs(dr) + eve::abs(di) < fp_min) dr = fp_min;
          fact = a / (cr * cr + ci * ci);
          cr = br + cr * fact;
          ci = bi - ci * fact;
          if (eve::abs(cr) + eve::abs(ci) < fp_min) cr = fp_min;
          den = dr * dr + di * di;
          dr /= den;
          di /= -den;
          dlr = cr * dr - ci * di;
          dli = cr * di + ci * dr;
          temp = p * dlr - q * dli;
          q = p * dli + q * dlr;
          p = temp;
          if (eve::abs(dlr - T(1)) + eve::abs(dli) < Eps)  break;
        }
        if (i > max_iter) return  kumi::make_tuple(nan(as(x)), nan(as(x)), nan(as(x)), nan(as(x)));
      }
      const T gam = (p - f) / q;
      jmu = eve::sqrt(w / ((p - f) * gam + q));
      jmu = eve::copysign(jmu, jnul);
      nmu = gam * jmu;
      npmu = (p + q / gam) * nmu;
      nnu1 = mu * xi * nmu - npmu;
    }
    fact = jmu / jnul;
    jnu = fact * jnul1;
    jpnu = fact * jpnu1;
    for (int i = 1; i <= nl; ++i)
    {
      const T nnutemp = (mu + i) * xi2 * nnu1 - nmu;
      nmu = nnu1;
      nnu1 = nnutemp;
    }
    nnu = nmu;
    npnu = nu * xi * nmu - nnu1;

    if(reflect)
    {
      auto [sp, cp] = sinpicospi(nu);
      jnu = cp*jnu-sp*nnu;
      nnu = cp*jnu+sp*nnu;
    }
    return kumi::make_tuple(jnu, jpnu, nnu, npnu);
  }

  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto bessel_jy(T nu, T x) noexcept
  {
    auto reflect(is_ltz(nu));
    nu =  eve::abs(nu); // v is non-negative from here
    auto iseqzx = is_eqz(x);
    auto isltzx = is_ltz(x);
    x = if_else(isltzx, zero, x);
    T jnu, jpnu, nnu, npnu;
    const T Eps = eve::eps(as(x));
    const T fp_min = eve::sqrt(smallestposval(as(x)));
    constexpr int max_iter = 15000;
    const T x_min = T(2);
    auto  nl = if_else(x < x_min,  trunc(nu + T(0.5)), eve::max(0, trunc(nu - x + T(1.5))));
    const T mu = nu - nl;
    const T mu2 = sqr(mu);
    const T xi = if_else(iseqzx, x, rec(x));
    const T xi2 = xi + xi;
    T w = xi2 *invpi(as(x));
    T isign = one(as(x));
    T h = nu * xi;
    h = eve::max(h, fp_min);
    T b = xi2 * nu;
    T d(T(0));
    T c = h;
    {
      int i;
      auto test(false_(as(Eps)));
      for ( i = 1; i <= max_iter; ++i)
      {
        b += xi2;
        d = b - d;
        d = if_else(eve::abs(d) < fp_min, fp_min, d);
        c = b - rec(c);
        c = if_else(eve::abs(c) < fp_min, fp_min, c);
        d = rec(d);
        const T del = c * d;
        h *= del;
        isign = if_else(is_ltz(d), -isign, isign);
        test = eve::abs(del - T(1)) < Eps;
        if (eve::all(test)) break;
      }
      if(i == max_iter) h = if_else(test, h, nan(as(h)));
    }
    T jnul = isign * fp_min;
    T jpnul = h * jnul;
    T jnul1 = jnul;
    T jpnu1 = jpnul;
    T fact = nu * xi;
    auto l = nl;
    auto test = l >= one(as(x));
    while(eve::any(test))
    {
      T jnutemp = fma(fact, jnul, jpnul);
      fact = if_else(test, fact-xi, fact);
      jpnul = if_else(test,  fms(fact, jnutemp, jnul), jpnul);
      jnul =  if_else(test, jnutemp, jnul);
      l = dec(l);
      test = l >= one(as(x));
    }
    jnul =  if_else(is_eqz(jnul), Eps, jnul);
    T f = jpnul / jnul;

    auto case_lt = [ = ](auto x, T& nmu, T& npmu, T& nnu1, T& jmu){
      const T Pi = eve::pi(as(x));
      const T x2 = x / T(2);
      T fact = rec(sinpic(mu));
      T d = -eve::log(x2);
      T e = mu * d;
      T fact2 = sinhc(e);
      T gam1, gam2, gampl, gammi;
      auto gamma_temme = [&gam1, &gam2, &gampl, &gammi, Eps](auto mu) {
        auto gamma_e = T(0.57721566490153286060651209008240243104215933593992);
        gampl = rec(tgamma(inc(mu)));
        gammi = rec(tgamma(oneminus(mu)));
        gam1 = if_else(eve::abs(mu) < Eps, gamma_e, (gammi - gampl) /(mu+mu));
        gam2 = average(gammi, gampl);
        return;
      };
      gamma_temme(mu);
      T ff = (T(2)/Pi)*fact * fma(gam1, eve::cosh(e), gam2 * fact2 * d);
      e = eve::exp(e);
      T p = e/(Pi*gampl);
      T q = rec(e*Pi*gammi);
      T muo2 = mu*T(0.5);
      T fact3 = sinpic(muo2);
      T r = sqr(Pi*fact3)*muo2;
      T c = T(1);
      d = -x2 * x2;
      T sum = ff + r * q;
      T sum1 = p;
      {
        int i;
        for (i = 1; i <= max_iter; ++i)
        {
          ff = (i * ff + p + q) / (i * i - mu2);
          c *= d / T(i);
          p /= T(i) - mu;
          q /= T(i) + mu;
          const T del = c * (ff + r * q);
          sum += del;
          const T del1 = c * p - i * del;
          sum1 += del1;
          auto test = eve::abs(del) < Eps * (T(1) + eve::abs(sum));
          if ( eve::all(test) ) break;
        }
        if(i == max_iter)
        {
          sum = if_else(test, sum, nan(as(sum)));
          sum1= if_else(test, sum1, nan(as(sum)));
        }
      }

      nmu = -sum;
      nnu1 = -sum1 * xi2;
      npmu = mu * xi * nmu - nnu1;
      jmu = w / (npmu - f * nmu);
      return;
    };

    auto case_ge = [ = ](auto x, T& nmu, T& npmu, T& nnu1, T& jmu){
      T a = T(0.25L) - mu2;
      T q = T(1);
      T p = -xi / T(2);
      T br = T(2) * x;
      T bi = T(2);
      T fact = a * xi / (p * p + q * q);
      T cr = br + q * fact;
      T ci = bi + p * fact;
      T den = br * br + bi * bi;
      T dr = br / den;
      T di = -bi / den;
      T dlr = cr * dr - ci * di;
      T dli = cr * di + ci * dr;
      T temp = p * dlr - q * dli;
      q = p * dli + q * dlr;
      p = temp;
      int i;
      for (i = 2; i <= max_iter; ++i)
      {
        a += T(2 * (i - 1));
        bi += T(2);
        dr = a * dr + br;
        di = a * di + bi;
        dr = if_else(eve::abs(dr) + eve::abs(di) < fp_min, fp_min, dr);
        fact = a / (cr * cr + ci * ci);
        cr = br + cr * fact;
        ci = bi - ci * fact;
        cr = if_else(eve::abs(cr) + eve::abs(ci) < fp_min, fp_min, cr);
        den = dr * dr + di * di;
        dr /= den;
        di /= -den;
        dlr = cr * dr - ci * di;
        dli = cr * di + ci * dr;
        temp = p * dlr - q * dli;
        q = p * dli + q * dlr;
        p = temp;
        auto test = eve::abs(dlr - T(1)) + eve::abs(dli) < Eps;
        if ( eve::all(test) ) break;
      }
      const T gam = (p - f) / q;
      jmu = eve::sqrt(w / ((p - f) * gam + q));
      jmu = eve::copysign(jmu, jnul);
      nmu = gam * jmu;
      npmu = (p + q / gam) * nmu;
      nnu1 = mu * xi * nmu - npmu;
      return;
    };

    T nmu, nnu1, npmu, jmu;
    auto xltx_min = x < x_min;
    if (eve::all(xltx_min))
    {
      case_lt(x, nmu, npmu, nnu1, jmu);
    }
    else if (eve::none(xltx_min))
    {
      case_ge(x, nmu, npmu, nnu1, jmu);
    }
    else
    {
      T nmutmp1, npmutmp1, nnu1tmp1, jmutmp1;
      T nmutmp2, npmutmp2, nnu1tmp2, jmutmp2;
      T mxx = eve::max(x, x_min);
      T mix = eve::min(x, x_min);
      case_lt(mix, nmutmp1, npmutmp1, nnu1tmp1, jmutmp1);

      case_ge(mxx, nmutmp2, npmutmp2, nnu1tmp2, jmutmp2);
      nmu  = if_else(xltx_min, nmutmp1 , nmutmp2);
      npmu = if_else(xltx_min, npmutmp1, npmutmp2);
      nnu1 = if_else(xltx_min, nnu1tmp1, nnu1tmp2);
      jmu  = if_else(xltx_min, jmutmp1 , jmutmp2);
    }
    fact = jmu / jnul;
    jnu = fact * jnul1;
    jpnu = fact * jpnu1;
    auto i = one(as(x));
    test = i <= nl;
    while (eve::any(test))
    {
      T nnutemp = (mu + i) * xi2 * nnu1 - nmu;
      nmu  = if_else(test, nnu1, nmu);
      nnu1 = if_else(test, nnutemp, nnu1);
      i = inc(i);
      test = i <= nl;
    }
    nnu = nmu;
    npnu = nu * xi * nmu - nnu1;
    if (eve::any(iseqzx))
    {
      auto iseqznu = is_eqz(nu);
      jnu = if_else(iseqzx, if_else(iseqznu, T(1), zero), jnu);
      jpnu= if_else(iseqzx,
                    if_else(iseqznu, zero,
                            if_else(nu == one(as(nu)), T(0.5), jpnu)
                           )
                   , jpnu
                   );
      nnu = if_else(iseqzx, minf(as(x)), nnu);
      nnu1= if_else(iseqzx, inf(as(x)), nnu1);
    }
    if(eve::any(reflect))
    {
      auto [sp, cp] = sinpicospi(nu);
      jnu = if_else(reflect, cp*jnu-sp*nnu, jnu);
      nnu = if_else(reflect, cp*jnu+sp*nnu, nnu);
    }
    if (eve::any(isltzx))
    {
      jnu = if_else(isltzx, jnu, allbits);
      jpnu = if_else(isltzx, jpnu, allbits);
      nnu = if_else(isltzx, nnu, allbits);
      npnu = if_else(isltzx, npnu, allbits);
    }
    return kumi::make_tuple(jnu, jpnu, nnu, npnu);
  }
}
