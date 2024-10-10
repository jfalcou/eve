#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>

// Written originally by Edward Smith-Rowland.
//
// References:
//   (1) Handbook of Mathematical Functions,
//       Ed. Milton Abramowitz and Irene A. Stegun,
//       Dover Publications,
//       Section 9, pp. 355-434, Section 10 pp. 435-478
//   (2) The Gnu Scientific Library, http://www.gnu.org/software/gsl
//   (3) Numerical Recipes in C, by W. H. Press, S. A. Teukolsky,
//       W. T. Vetterling, B. P. Flannery, Cambridge University Press (1992),
//       2nd ed, pp. 246-249.

namespace eve::detail
{

/**
 *   @brief  Compute the modified Bessel functions @f$ I_\nu(x) @f$ and
 *           @f$ K_\nu(x) @f$ and their first derivatives
 *           @f$ I'_\nu(x) @f$ and @f$ K'_\nu(x) @f$ respectively.
 *           These four functions are computed together for numerical
 *           stability.
 *
 *   @param  nu  The order of the Bessel functions.
 *   @param  x   The argument of the Bessel functions.
 *   @param  Inu  The output regular modified Bessel function.
 *   @param  Knu  The output irregular modified Bessel function.
 *   @param  Ipnu  The output derivative of the regular
 *                   modified Bessel function.
 *   @param  Kpnu  The output derivative of the irregular
 *                   modified Bessel function.
 */
template<floating_value T> constexpr
auto
kernel_bessel_ik(T nu, T x) noexcept
requires(simd_value<T>)
{
  auto iseqzx = is_eqz(x);
  auto isltzx = is_ltz(x);
  x           = if_else(isltzx, zero, x);
  T          Inu, Knu, Ipnu, Kpnu;
  const auto Eps      = eps(as{x});
  const T    fp_min   = T(10) * Eps;
  const int  max_iter = 15000;
  const T    x_min    = T(2);

  auto reflect(is_ltz(nu));
  nu = eve::abs(nu); // nu is non-negative from here

  //    auto  nl = if_else(x < x_min,  trunc(nu + T(0.5)), eve::max(0, trunc(nu - x + T(1.5))));
  auto nl = trunc(nu + T(0.5));
  //    const int nl = static_cast<int>(nu + T(0.5L));

  const T mu  = nu - nl;
  const T mu2 = sqr(mu);
  const T xi  = if_else(iseqzx, x, rec[pedantic](x));
  const T xi2 = xi + xi;

  T h = nu * xi;
  h   = eve::max(h, fp_min);
  T b = xi2 * nu;
  T d(T(0));
  T c = h;

  auto test = false_(as{Eps});
  int  i;
  for( i = 1; i <= max_iter; ++i )
  {
    b += xi2;
    d           = rec[pedantic](b + d);
    c           = b + rec[pedantic](c);
    const T del = c * d;
    h *= del;
    test = (eve::abs(dec(del)) < Eps);
    if( eve::all(test) ) break;
  }
  if( i == max_iter ) h = if_else(test, h, nan(as{h}));
  T Inul  = fp_min;
  T Ipnul = h * Inul;
  T Inul1 = Inul;
  T Ipnu1 = Ipnul;
  T fact  = nu * xi;

  auto l = nl;
  test   = l >= one(as{x});
  while( eve::any(test) )
  {
    const T Inutemp = fma(fact, Inul, Ipnul);
    fact            = if_else(test, fact - xi, fact);
    Ipnul           = if_else(test, fma(fact, Inutemp, Inul), Ipnul);
    Inul            = if_else(test, Inutemp, Inul);
    --l;
    test = l >= one(as{x});
  }

  T    f       = Ipnul / Inul;
  auto case_lt = [=](auto xx, T& Kmu, T& Knu1){
    xx = if_else(is_eqz(xx), T(2), xx);
    const T x2    = xx / T(2);
    const T ffact  = rec[pedantic](sinpic(mu));
    T       dd     = -eve::log(x2);
    T       e     = mu * dd;
    const T fact2 = eve::sinhc(e);
    T       gam1, gam2, gampl, gammi;
    auto    gamma_temme = [&gam1, &gam2, &gampl, &gammi, Eps](auto mmu)
    {
      auto gamma_e = T(0.57721566490153286060651209008240243104215933593992);
      gampl        = rec[pedantic](tgamma(inc(mmu)));
      gammi        = rec[pedantic](tgamma(oneminus(mmu)));
      gam1         = if_else(eve::abs(mmu) < Eps, gamma_e, (gammi - gampl) / (mmu + mmu));
      gam2         = average(gammi, gampl);
      return;
    };
    gamma_temme(mu);
    T ff   = ffact * fma(gam1, eve::cosh(e), gam2 * fact2 * dd);
    T sum0  = ff;
    e      = eve::exp(e);
    T p    = e / (T(2) * gampl);
    T q    = T(1) / (T(2) * e * gammi);
    T cc    = T(1);
    dd      = sqr(x2);
    T sum1 = p;
    {
      int ii;
      for( ii = 1; ii <= max_iter; ++ii )
      {
        ff = (ii * ff + p + q) / (ii * ii - mu2);
        cc *= dd / ii;
        p /= ii - mu;
        q /= ii + mu;
        const T del = cc * ff;
        sum0 += del;
        const T del1 = cc * (p - ii * ff);
        sum1 += del1;
        auto test1 = eve::abs(del) < Eps * eve::abs(sum0);
        if( eve::all(test1) ) break;
      }
      if( ii > max_iter )
      {
        sum  = if_else(test, sum0, nan(as{sum0}));
        sum1 = if_else(test, sum1, nan(as{sum0}));
      }
    }
    Kmu  = sum0;
    Knu1 = sum1 * xi2;
    return;
  };

  auto case_ge = [=](auto xx, T& Kmu, T& Knu1)
  {
    T bb    = 2 * inc(xx);
    T dd    = rec[pedantic](bb);
    T delh = dd;
    T hh    = delh;
    T q1   = T(0);
    T q2   = T(1);
    T a1   = T(0.25) - mu2;
    T cc    = a1;
    T q    = cc;
    T a    = -a1;
    T s    = inc(q * delh);
    {
      int ii;
      auto test1(is_eqz(delh));
      for( ii = 2; ii <= max_iter; ++ii )
      {
        a -= 2 * (ii - 1);
        cc            = -a * cc / ii;
        const T qnew = (q1 - bb * q2) / a;
        q1           = q2;
        q2           = qnew;
        q += cc * qnew;
        bb += T(2);
        dd    = rec[pedantic](fam(bb, a, dd));
        delh = dec(bb * dd) * delh;
        hh += delh; // if_else(test, hh, hh+delh);
        const T dels = q * delh;
        s += dels; // if_else(test, s, s+dels);
        test1 = eve::abs(dels) < Eps * eve::abs(s);
        if( eve::all(test1) ) break;
      }
      if( ii > max_iter )
      {
        s = if_else(test1, s, nan(as{s}));
        hh = if_else(test1, hh, nan(as{hh}));
      }
    }

    hh    = a1 * hh;
    Kmu  = eve::sqrt(pio_2(as{xx}) / xx) * eve::exp(-xx) / s;
    Knu1 = Kmu * (mu + xx + T(0.5) - hh) * xi;

    return;
  };

  T Kmu, Knu1;
  x             = if_else(is_nan(x), T{2}, x);
  auto xltx_min = x < x_min;
  if( eve::all(xltx_min) ) { case_lt(x, Kmu, Knu1); }
  else if( eve::none(xltx_min) ) { case_ge(x, Kmu, Knu1); }
  else
  {
    T Kmutmp1, Knu1tmp1;
    T Kmutmp2, Knu1tmp2;
    T mxx = eve::max(x, x_min);
    T mix = eve::min(x, x_min);
    case_lt(mix, Kmutmp1, Knu1tmp1);
    case_ge(mxx, Kmutmp2, Knu1tmp2);
    Kmu  = if_else(xltx_min, Kmutmp1, Kmutmp2);
    Knu1 = if_else(xltx_min, Knu1tmp1, Knu1tmp2);
  }

  T    Kpmu    = fms(mu, xi * Kmu, Knu1);
  T    Inumu   = xi / fms(f, Kmu, Kpmu);
  auto invInul = rec[pedantic](Inul);
  Inu          = Inumu * Inul1 * invInul;
  Ipnu         = Inumu * Ipnu1 * invInul;
  i            = 1;
  test         = i <= nl;
  while( eve::any(test) )
  {
    const T Knutemp = fma((mu + i), xi2 * Knu1, Kmu);
    Kmu             = if_else(test, Knu1, Kmu);
    ;
    Knu1 = if_else(test, Knutemp, Knu1);
    i    = inc(i);
    test = i <= nl;
  }
  Knu  = Kmu;
  Kpnu = fms(nu, xi * Kmu, Knu1);
  Inu  = if_else(is_nan(Inu), inf(as{x}), Inu);
  Knu  = if_else(is_nan(Knu), inf(as{x}), Knu);

  if( eve::any(reflect) )
  {
    auto s = sinpi(nu);
    Inu += if_else(reflect, inv_pi(as{x}) * 2 * s * Knu, zero);
  }
  return kumi::make_tuple(Inu, Ipnu, Knu, Kpnu);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
template<floating_value T> constexpr
auto
kernel_bessel_ik(T nu, T x) noexcept
requires(scalar_value<T>)
{
  if( x == inf(as{x}) ) return kumi::make_tuple(T(0), nan(as{x}), T(0), nan(as{x}));
  else if( is_ltz(x) ) return kumi::make_tuple(nan(as{x}), nan(as{x}), nan(as{x}), nan(as{x}));
  else if( is_eqz(x) )
  {
    if( is_eqz(nu) )
    {
      return kumi::make_tuple(T(1), T(0), inf(as{x}), minf(as{x})); // inu, ipnu, knu, kpnu
    }
    else if( nu == one(as{x}) )
    {
      return kumi::make_tuple(T(0), T(0.5), inf(as{x}), minf(as{x})); // inu, ipnu, knu, kpnu
    }
    else
    {
      return kumi::make_tuple(T(0), T(0), inf(as{x}), minf(as{x})); // inu, ipnu, knu, kpnu
    }
  }
  T          Inu, Knu, Ipnu, Kpnu;
  const auto Eps      = eps(as{x});
  const T    fp_min   = T(10) * Eps;
  const int  max_iter = 15000;
  const T    x_min    = T(2);

  auto reflect(is_ltz(nu));
  nu = eve::abs(nu); // nu is non-negative from here

  const int nl = static_cast<int>(nu + T(0.5L));

  const T mu  = nu - nl;
  const T mu2 = sqr(mu);
  const T xi  = rec[pedantic](x);
  const T xi2 = T(2) * xi;
  T       h   = nu * xi;
  if( h < fp_min ) h = fp_min;
  T   b = xi2 * nu;
  T   d = T(0);
  T   c = h;
  for(int i = 1; i <= max_iter; ++i )
  {
    b += xi2;
    d           = rec[pedantic](b + d);
    c           = b + rec[pedantic](c);
    const T del = c * d;
    h *= del;
    if( eve::abs(del - T(1)) < Eps ) break;
  }
  T Inul  = fp_min;
  T Ipnul = h * Inul;
  T Inul1 = Inul;
  T Ipnu1 = Ipnul;
  T ffact  = nu * xi;
  for( int l = nl; l >= 1; --l )
  {
    const T Inutemp = fma(ffact, Inul, Ipnul);
    ffact -= xi;
    Ipnul = fma(ffact, Inutemp, Inul);
    Inul  = Inutemp;
  }
  T f = Ipnul / Inul;

  T Kmu, Knu1;
  if( x < x_min )
  {
    const T x2    = x / T(2);
    const T fct   = rec[pedantic](sinpic(mu));
    T       dd    = -eve::log(x2);
    T       e     = mu * dd;
    const T fact2 = eve::sinhc(e);
    T       gam1, gam2, gampl, gammi;
    auto    gamma_temme = [&gam1, &gam2, &gampl, &gammi, Eps](auto mmu)
    {
      auto gamma_e = T(0.57721566490153286060651209008240243104215933593992);
      gampl        = rec[pedantic](tgamma(inc(mmu)));
      gammi        = rec[pedantic](tgamma(oneminus(mmu)));
      gam1         = eve::abs(mmu) < Eps ? gamma_e : (gammi - gampl) / (mmu + mmu);
      gam2         = average(gammi, gampl);
      return;
    };
    gamma_temme(mu);
    T ff     = fct * fma(gam1, eve::cosh(e), gam2 * fact2 * dd);
    T sums   = ff;
    e        = eve::exp(e);
    T p      = e / (T(2) * gampl);
    T q      = T(1) / (T(2) * e * gammi);
    T cc     = T(1);
    d        = sqr(x2);
    T   sum1 = p;
    for(int i = 1; i <= max_iter; ++i )
    {
      ff = (i * ff + p + q) / (i * i - mu2);
      cc *= d / i;
      p /= i - mu;
      q /= i + mu;
      const T del = cc * ff;
      sums += del;
      const T del1 = cc * (p - i * ff);
      sum1 += del1;
      if( eve::abs(del) < Eps * eve::abs(sums) ) break;
    }
    Kmu  = sums;
    Knu1 = sum1 * xi2;
  }
  else
  {
    T bb   = 2 * inc(x);
    T dd   = rec[pedantic](bb);
    T delh = dd;
    T hh   = delh;
    T q1   = T(0);
    T q2   = T(1);
    T a1   = T(0.25) - mu2;
    T q = c = a1;
    T a     = -a1;
    T s     = inc(q * delh);
    {
      int i;
      for( i = 2; i <= max_iter; ++i )
      {
        a -= 2 * (i - 1);
        c            = -a * c / i;
        const T qnew = (q1 - bb * q2) / a;
        q1           = q2;
        q2           = qnew;
        q += c * qnew;
        bb += T(2);
        dd   = rec[pedantic](fam(bb, a, dd));
        delh = dec(bb * dd) * delh;
        hh += delh;
        const T dels = q * delh;
        s += dels;
        if( eve::abs(dels) < Eps * abs(s) ) break;
      }
      if( i > max_iter )
      {
        s = nan(as{s});
        hh = nan(as{s});
      }
    }

    hh   = a1 * hh;
    Kmu  = eve::sqrt(pio_2(as{x}) / x) * eve::exp(-x) / s;
    Knu1 = Kmu * (mu + x + T{0.5} - hh) * xi;
  }

  T    Kpmu    = fms(mu, xi * Kmu, Knu1);
  T    Inumu   = xi / fms(f, Kmu, Kpmu);
  auto invInul = rec[pedantic](Inul);
  Inu          = Inumu * Inul1 * invInul;
  Ipnu         = Inumu * Ipnu1 * invInul;
  for(int i = 1; i <= nl; ++i )
  {
    const T Knutemp = fma((mu + i), xi2 * Knu1, Kmu);
    Kmu             = Knu1;
    Knu1            = Knutemp;
  }
  Knu  = Kmu;
  Kpnu = fms(nu, xi * Kmu, Knu1);
  if( is_nan(Inu) ) Inu = inf(as{x});
  if( is_nan(Knu) ) Knu = inf(as{x});

  if( reflect )
  {
    auto s = sinpi(nu);
    Inu += inv_pi(as{x}) * 2 * s * Knu;
  }
  return kumi::make_tuple(Inu, Ipnu, Knu, Kpnu);
}
}
