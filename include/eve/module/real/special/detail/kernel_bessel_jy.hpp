//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>

#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/all.hpp>
#include <eve/function/min.hpp>
#include <eve/function/max.hpp>
#include <eve/function/none.hpp>
#include <eve/function/average.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/fam.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/pedantic/rem.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/log.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sinpic.hpp>
#include <eve/function/sinhc.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/tgamma.hpp>

#include <eve/function/sin.hpp>
#include <eve/function/cosh.hpp>

namespace eve::detail
{


//   // Calculate Y(v, x) and Y(v+1, x) by Temme's method, see
//   // Temme, Journal of Computational Physics, vol 21, 343 (1976)
//   template <floating_real_value T>
//   int temme_jy(T v, T x)
//   {
//     EVE_ASSERT(eve::abs(v) <= T(0.5));  // precondition for using this routine
//     auto tgamma1pm1 = [](auto x){ return dec(eve::tgamma(inc(x))); };
//     auto euler = T(0.57721566490153286060651209008240243);
//     T gp = tgamma1pm1(v);
//     T gm = tgamma1pm1(-v);
//     T spv = sinpi(v);
//     T spv2 = sinpi(v/2);
//     T xp = eve::pow(x/2, v);

//     T a = eve::log(x / 2);
//     T sigma = -a * v;
//     T d = sinhc(sigma);
//     T e = if_else(eve::abs(v) < eve::eps(as(x)), v*sqr(pi(as(x)))/2, 2*sqr(spv2)/v); //
//     T g1 =if_else( is_eqz(v), -euler, (gp - gm) / (inc(gp) * inc(gm) * 2 * v));
//     T g2 = (2 + gp + gm) / (inc(gp) * inc(gm) * 2);
//     T vspv = if_else(eve::abs(v) < eve::eps(as(x)), invpi(as(x)), v / spv); //
//     T f = (g1 * cosh(sigma) - g2 * a * d) * 2 * vspv;

//     T p = vspv / (xp * (1 + gm));
//     T q = vspv * xp / (1 + gp);

//     T g = fam(f, e, q);
//     T h = p;
//     T coef(1);
//     T sum = coef * g;
//     T sum1 = coef * h;

//     T v2 = v * v;
//     T coef_mult = -sqr(x/2);

//     // series summation
//     auto tolerance = eve::eps(as(x));
//     auto test(false_(as(x)));
//     for (int k = 1; k < 1500; ++k)
//     {
//       f = fma(k,  f,  p + q) / (sqr(k) - v2);
//       p /= k - v;
//       q /= k + v;
//       g = fma(e, q, f);
//       h = fnma(k, g, p); //p - k * g;
//       coef *= coef_mult / k;
//       sum = if_else(test, fam(sum, coef, g), sum);
//       sum1 =if_else(test, fam(sum1, coef, h), sum1);
//       test = abs(coef * g) < eve::abs(sum) * tolerance;
//       if (eve::all(test)) break;
//     }
//     return kumi::tuple<T, T>{ -sum, -2 * sum1 / x};
//   }

//   // Evaluate continued fraction fv = J_(v+1) / J_v, see
//   // Abramowitz and Stegun, Handbook of Mathematical Functions, 1972, 9.1.73
//   template <floating_real_value T> auto CF1_jy(T v, T x)
//   {
//     //  T* fv, int* sign, const Policy& po
//     // T C, D, f, a, b, delta, tiny, tolerance;
//     // unsigned long k;
//     // int s = 1;
//     // |x| <= |v|, CF1_jy converges rapidly
//     // |x| > |v|, CF1_jy needs O(|x|) iterations to converge

//     // modified Lentz's method, see
//     // Lentz, Applied Optics, vol 15, 668 (1976)
//     T tolerance = 2*eve::eps(as(x));
//     T tiny = sqrt(eve::smallestposval(as(x)));
//     T C(tiny);
//     T f(tiny);
//     T D(0);
//     T delta(0);
//     T s(1);
//     auto test(true_(as(x)));
//     for (int k = 1; k < 1500; ++k)
//     {
//       T a(-1);
//       T b(2 * (v + k) / x);
//       T C = b -rec(C);
//       T D = b-D;
//       C = if_else (is_eqz(C), tiny, C);
//       D = if_else (is_eqz(D), tiny, D);
//       D = rec(D);
//       delta = if_else(test, C * D, one);
//       f *= delta;
//       s = if_else (is_ltz(D)&&test -s, s);
//       test = eve::abs(dec(delta)) > tolerance;
//       if (eve::none(test)) break;

//     }
//     return kumi::tuple<T, T>{-f, s};
//   }


//   //
//   // This algorithm was originally written by Xiaogang Zhang
//   // using std::complex to perform the complex arithmetic.
//   // However, that turns out to 10x or more slower than using
//   // all real-valued arithmetic, so it's been rewritten using
//   // real values only.
//   //
//   template <floating_real_value T>
//   auto CF2_jy(T v, T x)
//   {
//     //T* p, T* q, const Policy& pol

// //     T Cr, Ci, Dr, Di, fr, fi, a, br, bi, delta_r, delta_i, temp;
// //     T tiny;
// //     unsigned long k;

//          // |x| >= |v|, CF2_jy converges rapidly
//          // |x| -> 0, CF2_jy fails to converge
//     EVE_ASSERT(eve::all(eve::abs(x) > 1), "some x are greater than 1");

//          // modified Lentz's method, complex numbers involved, see
//          // Lentz, Applied Optics, vol 15, 668 (1976)
//     T tolerance = 2 * eps(as(x));
//     T tiny = sqrt(eve::smallestposval(as(x)));
//     T invx = rec(x);
//     T Cr(-invx/2);
//     T fr(Cr);
//     T fi(1);
//     //Dr = Di = 0;
//     T v2 = sqr(v);
//     T a = (0.25f - v2) *invx; // Note complex this one time only!
//     T br = 2 * x;
//     T bi(2);
//     T temp = rec(inc(sqr(Cr)));
//     T Ci = bi + a * Cr * temp;
//     Cr = br + a * temp;
//     T Dr = br;
//     T Di = bi;
//     Cr = if_else (eve::abs(Cr) + eve::abs(Ci) < tiny, tiny, Cr);
//     Ci = if_else (eve::abs(Dr) + eve::abs(Di) < tiny, tiny, Dr);
//     temp = rec(sqr(Dr)+sqr(Di));
//     Dr = Dr* temp;
//     Di = -Di * temp;
//     T delta_r = Cr * Dr - Ci * Di;
//     T delta_i = Ci * Dr + Cr * Di;
//     temp = fr;
//     fr = temp * delta_r - fi * delta_i;
//     fi = temp * delta_i + fi * delta_r;
//     for (int k = 2; k < 1500; ++k)
//     {
//       a = sqr(k - T(0.5))-v2;
//       bi += 2;
//       temp = rec(sqr(Cr)+sqr(Ci));
//       Cr = br + a * Cr * temp;
//       Ci = bi - a * Ci * temp;
//       Dr = br + a * Dr;
//       Di = bi + a * Di;
//       Cr = if_else (eve::abs(Cr) + eve::abs(Ci) < tiny, tiny, Cr);
//       Ci = if_else (eve::abs(Dr) + eve::abs(Di) < tiny, tiny, Dr);
//       temp = rec(sqr(Dr)+sqr(Di));
//       Dr = Dr * temp;
//       Di = -Di * temp;
//       delta_r = Cr * Dr - Ci * Di;
//       delta_i = Ci * Dr + Cr * Di;
//       temp = fr;
//       fr = temp * delta_r - fi * delta_i;
//       fi = temp * delta_i + fi * delta_r;
//       auto test = eve::abs(dec(delta_r)) + eve::abs(delta_i) >  tolerance;
//       if (eve::none(test)) break;
//     }
//     return kumi::tuple<T,T>(fr, fi);
//   }

//   // Compute J(v, x) and Y(v, x) simultaneously by Steed's method, see
//   // Barnett et al, Computer Physics Communications, vol 8, 377 (1974)
//   template <floating_real_scalar_value T> int bessel_jy(T v, T x)
//   {
//     EVE_ASSERT(x >= 0, "x is negative");
//     EVE_ASSERT(frac(v)!= 0, "v is integral");
//     // T* J, T* Y, int kind, const Policy& pol
//     // T u, Jv, Ju, Yv, Yv1, Yu, Yu1(0), fv, fu;
//     // T W, p, q, gamma, current, prev, next;
//  //    unsigned n, k;
//  //          int s;
//  //          int org_kind = kind;
//  //          T cp = 0;
//  //          T sp = 0;

//     auto reflect(is_ltz(v));
//     v =  eve:abs(v); // v is non-negative from here
//     if (v > T(valmax(as(int())))) return kumi::tuple<T, T>(nan(as(x)), nan(as(x)));
//     auto n = inearest(v);
//     T u = v - n;                              // -1/2 <= u < 1/2 u != 0

//     if(reflect)
//     {
//       T z = (u + n % 2);
//       [sp cp] = sinpicospi(z);
//     }

//     if(is_eqz(x)&&!reflect) return kumi::<T, T>{ T(0), minf(as(x))};
//     // x is positive until reflection
//     T W = T(2) / (x * pi<T>());               // Wronskian
//     T Yv_scale(1);
//     if(((kind & need_y) == 0) && ((x < 1) || (v > x * x / 4) || (x < 5)))
//     {
//       //
//       // This series will actually converge rapidly for all small
//       // x - say up to x < 20 - but the first few terms are large
//       // and divergent which leads to large errors :-(
//       //
//       Jv = bessel_j_small_z_series(v, x, pol);
//       Yv = std::numeric_limits<T>::quiet_NaN();
//     }
//     else if((x < 1) && (u != 0) && (log(policies::get_epsilon<T, Policy>() / 2) > v * log((x/2) * (x/2) / v)))
//     {
//       // Evaluate using series representations.
//       // This is particularly important for x << v as in this
//       // area temme_jy may be slow to converge, if it converges at all.
//       // Requires x is not an integer.
//       if(kind&need_j)
//         Jv = bessel_j_small_z_series(v, x, pol);
//       else
//         Jv = std::numeric_limits<T>::quiet_NaN();
//       if((org_kind&need_y && (!reflect || (cp != 0)))
//          || (org_kind & need_j && (reflect && (sp != 0))))
//       {
//         // Only calculate if we need it, and if the reflection formula will actually use it:
//         Yv = bessel_y_small_z_series(v, x, &Yv_scale, pol);
//       }
//       else
//         Yv = std::numeric_limits<T>::quiet_NaN();
//     }
//     else if(asymptotic_bessel_large_x_limit(v, x))
//     {
//       Yv = asymptotic_bessel_y_large_x_2(v, x);
//       Jv = asymptotic_bessel_j_large_x_2(v, x);
//     }
//     else
//     {
//       //
//       // Simultaneous calculation of A&S 9.2.9 and 9.2.10
//       // for use in A&S 9.2.5 and 9.2.6.
//       // This series is quick to evaluate, but divergent unless
//       // x is very large, in fact it's pretty hard to figure out
//       // with any degree of precision when this series actually
//       // *will* converge!!  Consequently, we may just have to
//       // try it and see...
//       //
//       T p, q;
//       auto hankel_PQ = [&p, &q](T v, T x)
//         {
//           T const tolerance = 2 * eps(as(x));
//           p = T(1);
//           q = T(0);
//           T k(1);
//           T z8(8 * x);
//           T sq(1);
//           T mu(sqr(2*v));
//           T term(1);
//           auto ok(true_(as(x)));
//           auto test(ok);
//           do
//           {
//             term *= (mu - sqr(sq)) / (k * z8);
//             q += term;
//             k = inc(k);
//             sq += 2;
//             T mult = (sqr(sq) - mu) / (k * z8);
//             ok = eve::abs(mult) < T(0.5);
//             term = if_else(ok, term*mult, term);
//             p = if_else(ok, p+term, p);
//             k = inc(k);
//             sq += 2;
//             test = (eve::abs(term) > tolerance*p) && ok;
//           }
//           while(eve::any(test));
//           return ok;
//         };
//       if((x > 8) && hankel_PQ(v, x))
//       {
//         //
//         // Hankel approximation: note that this method works best when x
//         // is large, but in that case we end up calculating sines and cosines
//         // of large values, with horrendous resulting accuracy.  It is fast though
//         // when it works....
//         //
//         // Normally we calculate sin/cos(chi) where:
//         //
//         // chi = x - fmod(T(v / 2 + 0.25f), T(2)) * boost::math::constants::pi<T>();
//         //
//         // But this introduces large errors, so use sin/cos addition formulae to
//         // improve accuracy:
//         //
//         T mod_v = eve::fmod(v / 2 + T(0.25)), T(2));
//       [sx, cx]= sincos(x);
//       [sv, cv]= sinpicospi(mod_v);

//       T sc = sx * cv - sv * cx; // == sin(chi);
//       T cc = cx * cv + sx * sv; // == cos(chi);
//       //            T chi = boost::math::constants::root_two<T>() / (boost::math::constants::root_pi<T>() * sqrt(x)); //sqrt(2 / (boost::math::constants::pi<T>() * x));
//       T chi = eve::rsqrt(pio_2(as(x))*x);
//       Yv = chi * (p * sc + q * cc);
//       Jv = chi * (p * cc - q * sc);
//     }
//     else if (x <= 2)                           // x in (0, 2]
//     {
//       [Yu, Yu1] = temme_jy(u, x);
//       //             if(temme_jy(u, x, &Yu, &Yu1, pol))             // Temme series
//       //              {
//       //                // domain error:
//       //                *J = *Y = Yu;
//       //                return 1;
//       //             }
//       auto prev = Yu;
//       auto current = Yu1;
//       T scale(1);
//       for (k = 1; k <= n; ++k)            // forward recurrence for Y
//       {
//         T fact = 2 * (u + k) / x;
//         auto test = (valmax(as(x)) - eve::abs(prev)) / fact < eve::abs(current);
//         if(eve::any(test))
//         {
//           scale = if_else(test, scale/current, scale);
//           prev =  if_else(test, prev/current, prev);
//           current = if_else(test, one, current);
//         }
//         next = fact * current - prev;
//         prev = current;
//         current = next;
//       }
//       Yv = prev;
//       Yv1 = current;
//       [fv, s] = CF1_jy(v, x);                 // continued fraction CF1_jy
//       Jv = scale * W / (Yv * fv - Yv1);       // Wronskian relation
//       Yv_scale = scale;
//     }
//     else                                    // x in (2, \infty)
//     {
//       // Get Y(u, x):

//       T ratio;
//       [fv, s] = CF1_jy(v, x);
//       // tiny initial value to prevent overflow
//       T init = sqrt(smallestposval(as(x)));
//       prev = fv * s * init;
//       current = s * init;
//       if(v < 170)//max_factorial<T>::value)
//       {
//         for (k = n; k > 0; k--)             // backward recurrence for J
//         {
//           next = 2 * (u + k) * current / x - prev;
//           prev = current;
//           current = next;
//         }
//         ratio = (s * init) / current;     // scaling ratio
//         // can also call CF1_jy() to get fu, not much difference in precision
//         fu = prev / current;
//       }
//       else
//       {
//         //
//         // When v is large we may get overflow in this calculation
//         // leading to NaN's and other nasty surprises:
//         //
//         bool over = false;
//         for (k = n; k > 0; k--)             // backward recurrence for J
//         {
//           T t = 2 * (u + k) / x;
//           if((t > 1) && (valmax(as(x)) / t < current))
//           {
//             over = true;
//             break;
//           }
//           next = t * current - prev;
//           prev = current;
//           current = next;
//         }
//         T ratio(0);
//         T fu(1);
//         if(!over)
//         {
//           ratio = (s * init) / current;     // scaling ratio
//           // can also call CF1_jy() to get fu, not much difference in precision
//           fu = prev / current;
//         }
//       }
//       [p, q] = CF2_jy(u, x);                  // continued fraction CF2_jy
//       T t = u / x - fu;                   // t = J'/J
//       gamma = (p - t) / q;
//       //
//       // We can't allow gamma to cancel out to zero completely as it messes up
//       // the subsequent logic.  So pretend that one bit didn't cancel out
//       // and set to a suitably small value.  The only test case we've been able to
//       // find for this, is when v = 8.5 and x = 4*PI.
//       //
//       if(gamma == 0)
//       {
//         gamma = u * eps(as(x)) / x;
//       }
//       Ju = sign(current) * sqrt(W / (q + gamma * (p - t)));
//       Jv = Ju * ratio;                    // normalization

//       Yu = gamma * Ju;
//       Yu1 = Yu * (u/x - p - q/gamma);
//       // compute Y:
//       prev = Yu;
//       current = Yu1;
//       for (k = 1; k <= n; k++)            // forward recurrence for Y
//       {
//         T fact = 2 * (u + k) / x;
//         if((tools::max_value<T>() - fabs(prev)) / fact < fabs(current))
//         {
//           prev /= current;
//           Yv_scale /= current;
//           current = 1;
//         }
//         next = fact * current - prev;
//         prev = current;
//         current = next;
//       }
//       Yv = prev;


//       if (reflect)
//       {
//         J = cp * Jv - (sp == 0 ? T(0) : T((sp * Yv) / Yv_scale));
//         Y = (sp != 0 ? sp * Jv : T(0)) + (cp == 0 ? T(0) : T((cp * Yv) / Yv_scale));
//       }
//       else
//       {
//         J = Jv;
//         Y = Yv / Yv_scale;
//       }
//       return kumi::tuple<T, T>{J, Y};
//     }
//   }





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
