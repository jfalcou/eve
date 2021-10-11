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
#include <eve/function/abs.hpp>
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/function/cyl_bessel_j1.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/nthroot.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sinpicospi.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/kumi.hpp>

namespace eve::detail
{

  template <class T>
  inline T asymptotic_bessel_amplitude(T v, T x)
  {
    // Calculate the amplitude of J(v, x) and Y(v, x) for large
    // x: see A&S 9.2.28.
    T s = 1;
    T mu = 4 * v * v;
    T txq = 2 * x;
    txq *= txq;

    s += (mu - 1) / (2 * txq);
    s += 3 * (mu - 1) * (mu - 9) / (txq * txq * 8);
    s += 15 * (mu - 1) * (mu - 9) * (mu - 25) / (txq * txq * txq * 8 * 6);

    return sqrt(s * 2 / (pi(as(x)) * x));
  }

  template <class T>
  T asymptotic_bessel_phase_mx(T v, T x)
  {
    //
    // Calculate the phase of J(v, x) and Y(v, x) for large x.
    // See A&S 9.2.29.
    // Note that the result returned is the phase less (x - PI(v/2 + 1/4))
    // which we'll factor in later when we calculate the sines/cosines of the result:
    //
    T mu = 4 * v * v;
    T denom = 4 * x;
    T denom_mult = denom * denom;

    T s = 0;
    s += (mu - 1) / (2 * denom);
    denom *= denom_mult;
    s += (mu - 1) * (mu - 25) / (6 * denom);
    denom *= denom_mult;
    s += (mu - 1) * (mu * mu - 114 * mu + 1073) / (5 * denom);
    denom *= denom_mult;
    s += (mu - 1) * (5 * mu * mu * mu - 1535 * mu * mu + 54703 * mu - 375733) / (14 * denom);
    return s;
  }

  template <class T>
  inline T asymptotic_bessel_y_large_x_2(T v, T x)
  {
    // See A&S 9.2.19.
    // Get the phase and amplitude:
    T ampl = asymptotic_bessel_amplitude(v, x);
    T phase = asymptotic_bessel_phase_mx(v, x);
    //
    // Calculate the sine of the phase, using
    // sine/cosine addition rules to factor in
    // the x - PI(v/2 + 1/4) term not added to the
    // phase when we calculated it.
    //
    auto [sx, cx] = sincos(x);
    auto [si, ci] = sinpicospi(v / 2 + 0.25f);
    T sin_phase = sin(phase) * (cx * ci + sx * si) + cos(phase) * (sx * ci - cx * si);
    return sin_phase * ampl;
  }

  template <class T>
  inline T asymptotic_bessel_j_large_x_2(T v, T x)
  {
    // See A&S 9.2.19.
    // Get the phase and amplitude:
    T ampl = asymptotic_bessel_amplitude(v, x);
    T phase = asymptotic_bessel_phase_mx(v, x);
    //
    // Calculate the sine of the phase, using
    // sine/cosine addition rules to factor in
    // the x - PI(v/2 + 1/4) term not added to the
    // phase when we calculated it.
    //

    auto [sx, cx] = sincos(x);
    auto [si, ci] = sinpicospi(v / 2 + 0.25f);
    T sin_phase = cos(phase) * (cx * ci + sx * si) - sin(phase) * (sx * ci - cx * si);
    return sin_phase * ampl;
  }

  template <class T>
  inline bool asymptotic_bessel_large_x_limit(int v, const T& x)
  {
    //
    // Determines if x is large enough compared to v to take the asymptotic
    // forms above.  From A&S 9.2.28 we require:
    //    v < x * eps^1/8
    // and from A&S 9.2.29 we require:
    //    v^12/10 < 1.5 * x * eps^1/10
    // using the former seems to work OK in practice with broadly similar
    // error rates either side of the divide for v < 10000.
    // At double precision eps^1/8 ~= 0.01.
    //
    return (v ? v : 1) < x * 0.004f;
  }

  template <class T>
  inline bool asymptotic_bessel_large_x_limit(const T& v, const T& x)
  {
    //
    // Determines if x is large enough compared to v to take the asymptotic
    // forms above.  From A&S 9.2.28 we require:
    //    v < x * eps^1/8
    // and from A&S 9.2.29 we require:
    //    v^12/10 < 1.5 * x * eps^1/10
    // using the former seems to work OK in practice with broadly similar
    // error rates either side of the divide for v < 10000.
    // At double precision eps^1/8 ~= 0.01.
    //
    return (eve::max)(T(eve::abs(v)), T(1)) < x * eve::nthroot(eve::eps(as(x)), 8); //sqrt(tools::forth_root_epsilon<T>());
  }



//   // Evaluate continued fraction fv = J_(v+1) / J_v, see
//   // Abramowitz and Stegun, Handbook of Mathematical Functions, 1972, 9.1.73
//   template <typename T>
//   EVE_FORCEINLINE auto CF1_jy(T v, T x) noexcept
//   {
//     T C, D, f, a, b, delta, tiny, tolerance;
//     unsigned long k;
//     int s = 1;
//     // |x| <= |v|, CF1_jy converges rapidly
//     // |x| > |v|, CF1_jy needs O(|x|) iterations to converge

//     // modified Lentz's method, see
//     // Lentz, Applied Optics, vol 15, 668 (1976)
//     tolerance = 2 * eve::eps(as(x));
//     tiny = eve::sqrt(valmin(as(x)));
//     C = f = tiny;                           // b0 = 0, replace with tiny
//     D = 0;
//     for (k = 1; k < 1000; ++k)//policies::get_max_series_iterations<Policy>() * 100; k++)
//     {
//       a = -1;
//       b = 2 * (v + k) / x;
//       C = b + a / C;
//       D = b + a * D;
//       if (C == 0) { C = tiny; }
//       if (D == 0) { D = tiny; }
//       D = rec(D);
//       delta = C * D;
//       f *= delta;
//       if (D < 0) { s = -s; }
//       if (eve::abs(delta - 1) < tolerance) break;
//     }
//     return kumi::tuple<T, T>{-f, s};
//   }

  /////////////////////////////////////////////////////////////////////////
  // bessel_j of integer order
  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_j_int (I n, T x) noexcept
  {
    // n < abs(z), forward recurrence stable and usable
    // n >= abs(z), forward recurrence unstable, use Miller's algorithm
    EVE_ASSERT(eve::all(is_flint(n)); "n is not a floating integer");
    auto j0 = cyl_bessel_j0(x);
    auto j1 = cyl_bessel_j1(x);

    // Evaluate continued fraction fv = J_(v+1) / J_v, see
    // Abramowitz and Stegun, Handbook of Mathematical Functions, 1972, 9.1.73
    auto CF1_jy = [](T v, T x) noexcept
      {
        std::cout << " CF1_jy" << std::endl;
        T C, D, f, a, b, delta, tiny, tolerance;
        unsigned long k;
        T s(1);
        // |x| <= |v|, CF1_jy converges rapidly
        // |x| > |v|, CF1_jy needs O(|x|) iterations to converge

        // modified Lentz's method, see
        // Lentz, Applied Optics, vol 15, 668 (1976)
        tolerance = 2 * eve::eps(as(x));
        tiny = eve::sqrt(valmin(as(x)));
        C = f = tiny;                           // b0 = 0, replace with tiny
        D = 0;
        for (k = 1; k < 1000; ++k)//policies::get_max_series_iterations<Policy>() * 100; k++)
        {
          a = -1;
          b = 2 * (v + k) / x;
          C = b + a / C;
          D = b + a * D;
          C = if_else(is_eqz(C), tiny, C);
          D = if_else(is_eqz(D), tiny, D);
          D = rec(D);
          delta = C * D;
          f *= delta;
          D = if_else (is_ltz(D), -s, s);
          if (eve::all(eve::abs(delta - 1) < tolerance)) break;
        }
        return kumi::tuple<T, T>{-f, s};
      };
    auto br_large =  [](auto n,  auto x)
      {
        std::cout << "br_large" << std::endl;
        return asymptotic_bessel_j_large_x_2(T(n), x);
      };
    auto br_forward =  [j0, j1](auto n,  auto x)
      {
        std::cout << "br_forward" << std::endl;
        auto prev = j0; //cyl_bessel_j0(x);
        auto current = j1; //cyl_bessel_j1(x);
        T scale(1), value(0);
        for (int k = 1; k < n; k++)
        {
          T fact = 2 * k / x;
          // rescale if we would overflow or underflow:
          if((eve::abs(fact) > 1) && ((valmax(as(x)) - eve::abs(prev)) / eve::abs(fact) < eve::abs(current)))
          {
            scale /= current;
            prev /= current;
            current = 1;
          }
          value = fms(fact, current, prev);
          prev = current;
          current = value;
        };
        return value/scale;
      };
    auto br_small =  [](auto ,  auto x)
      {
        std::cout << "br_small" << std::endl;
        return x; //bessel_j_small_z_series(T(n), x);
      };
    auto br_backward =  [CF1_jy, j0](auto n,  auto x)
      {
        std::cout << "br_backward" << std::endl;
        T scale(1);
        // fn = J_(n+1) / J_n
        // |x| <= n, fast convergence for continued fraction CF1
        auto [fn, s] = CF1_jy(T(n), x);
        ///T fn(0); //, s(0);
        auto prev = fn;
        auto current = one(as(x));
        for (int k = n; k > 0; k--)
        {
          T fact = 2 * k / x;
          if((eve::abs(fact) > 1) && ((valmax(as(x)) - eve::abs(prev)) / eve::abs(fact) < eve::abs(current)))
          {
            prev /= current;
            scale /= current;
            current = 1;
          }
          auto next = fact * current - prev;
          prev = current;
          current = next;
        }
        auto value = j0 / current;       // normalization
        return value *scale;
      };

    if constexpr(scalar_value<I> && scalar_value<T>)
    {
      std::cout << " kernel_bessel_j_int scalar scalar" << std::endl;
      T factor(1);
      auto isoddn = is_odd(n);
      if (n < 0)
      {
        factor = T(isoddn ? -1 : 1);  // J_{-n}(z) = (-1)^n J_n(z)
        n = -n;
      }
      auto xlt0 = is_ltz(x);
      factor *=  T(xlt0 && isoddn ? -1:1);  // J_{n}(-z) = (-1)^n J_n(z)
      x = if_else(xlt0, -x, x);
      if (x == inf(as(x)))                          return zero(as(x));
      if (asymptotic_bessel_large_x_limit(T(n), x)) return factor*br_large(T(n), x);
      if (n == 0)                                   return cyl_bessel_j0(x);
      if (n == 1)                                   return factor*cyl_bessel_j1(x);
      if (is_eqz(x))                                return factor*x;   // as n >= 2
      if (n < abs(x))                               return br_forward(n, x);      // forward recurrence
      if ((x < 1) || (n > x * x / 4) || (x < 5))    return factor*br_small(n, x); // serie
        return br_backward(x, n);     // backward recurrence
    }
    else
    {
    }
    return x;
  }

  template<floating_real_value I, floating_real_value T>
  EVE_FORCEINLINE auto  kernel_bessel_j_flt (I , T x) noexcept
  {
    EVE_ASSERT(eve::none(is_flint(nu)); "some nu are floating integers");
    if(scalar_value<I>)
    {
    }
    else
    {
    }
    return x;
  }

}
