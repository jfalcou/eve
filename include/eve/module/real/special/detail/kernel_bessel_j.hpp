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
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/function/cyl_bessel_j1.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_eqz.hpp>
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
#include <eve/module/real/special/detail/kernel_bessel_jy.hpp>

namespace eve::detail
{

  template <class F, class U, class V>
  inline auto sum_series( F& func
                         , U factor
                         , int max_terms
                         , V init_value) noexcept
  {
    using result_type =  typename F::result_type;

    int counter = max_terms;

    result_type result(init_value);
    result_type next_term;
    do{
      next_term = func();
      result += next_term;
    }
    while(eve::any(abs(factor * result) < eve::abs(next_term)) && --counter);

    // set max_terms to the actual number of terms of the series evaluated:
    max_terms = max_terms - counter;

    return result;
  }

  template <class T>
  struct bessel_j_small_z_series_term
  {
    typedef T result_type;

    bessel_j_small_z_series_term(T v_, T x)
      : N(0), v(v_)
    {
      mult = x / 2;
      mult *= -mult;
      term = 1;
    }
    T operator()()
    {
      T r = term;
      ++N;
      term *= mult / (N * (N + v));
      return r;
    }
  private:
    unsigned N;
    T v;
    T mult;
    T term;
  };

  //
  // Series evaluation for BesselJ(v, z) as z -> 0.
  // See http://functions.wolfram.com/Bessel-TypeFunctions/BesselJ/06/01/04/01/01/0003/
  // Converges rapidly for all z << v.
  //
  template <class T>
  inline T bessel_j_small_z_series(T v, T x)
  {
//    std::cout << "bessel_j_small_z_series" << std::endl;
    T prefix;
    using elt_t = element_type_t<T>;
    auto max_factorial = (sizeof(elt_t) == 4 ? 34 : 170);
    auto test = v < max_factorial;
    prefix = if_else(test
                    , eve::pow(x / 2, v) / eve::tgamma(v+1)
                    , eve::exp(v * eve::log(x / 2) - eve::lgamma(v+1))
                    );
    if(eve::all(is_eqz(prefix)))  return prefix;
    bessel_j_small_z_series_term<T> s(v, x);
    auto max_iter = 1000000;
    T result = sum_series(s, eps(as(x)), max_iter, zero(as(x)));
    return prefix * result;
  }




  template <class T>
  inline T asymptotic_bessel_amplitude(T v, T x)
  {
    // Calculate the amplitude of J(v, x) and Y(v, x) for large
    // x: see A&S 9.2.28.
    T s(1);
    T mu = 4 * sqr(v);
    T txq = 2 * x;
    txq *= txq;
    auto mum1 = dec(mu);
    s += (mum1) / (2 * txq);
    s += 3 * (mum1) * (mu - 9) / (txq * txq * 8);
    s += 15 * (mum1) * (mu - 9) * (mu - 25) / (txq * txq * txq * 8 * 6);

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
    auto mum1 = dec(mu);

    T s(0);
    s += (mum1) / (2 * denom);
    denom *= denom_mult;
    s += (mum1) * (mu - 25) / (6 * denom);
    denom *= denom_mult;
    s += (mum1) * (mu * mu - 114 * mu + 1073) / (5 * denom);
    denom *= denom_mult;
    s += (mum1) * (5 * mu * mu * mu - 1535 * mu * mu + 54703 * mu - 375733) / (14 * denom);
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
    auto [sp, cp] = sincos(phase);
    T sin_phase = cp * (cx * ci + sx * si) - sp * (sx * ci - cx * si);
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
    auto vv = if_else(is_nez(v), v,  one);
    return vv < x * 0.004f;
  }

  template <class T>
  inline auto asymptotic_bessel_large_x_limit(const T& v, const T& x)
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

  /////////////////////////////////////////////////////////////////////////
  // bessel_j of integer order
  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_j_int (I n, T x) noexcept
  {
    // n < abs(z), forward recurrence stable and usable
    // n >= abs(z), forward recurrence unstable, use Miller's algorithm
    EVE_ASSERT(eve::all(is_flint(n)); "kernel_bessel_j_int : somme n are not floating integer");
    auto j0 = cyl_bessel_j0(x);
    auto j1 = cyl_bessel_j1(x);

    auto br_large =  [](auto n,  auto x)
      {
        //       std::cout << "br_large" << std::endl;
        return asymptotic_bessel_j_large_x_2(T(n), x);
      };
    auto br_forward =  [j0, j1](auto n,  auto x)
      {
        //        std::cout << "br_forward" << std::endl;
        auto prev = j0; //cyl_bessel_j0(x);
        auto current = j1; //cyl_bessel_j1(x);
        T scale(1), value(0);
        for (int k = 1; k < eve::maximum(n); k++)
        {
          T fact = 2 * k / x;
          // rescale if we would overflow or underflow:
          auto test = (eve::abs(fact) > 1) && ((valmax(as(x)) - eve::abs(prev)) / eve::abs(fact) < eve::abs(current));
          if (eve::any(test))
          {

            scale = if_else(test, scale/current, scale);
            prev  = if_else(test, prev/current,  prev);
            current = if_else(test, one, current);
          }
          value = fms(fact, current, prev);
          prev = current;
          current = value;
        };
        return value/scale;
      };
    auto br_small =  [](auto n,  auto x)
      {
        //        std::cout << "br_small" << std::endl;
        return bessel_j_small_z_series(T(n), x);
      };
    auto br_backward =  [](auto n,  auto x)
      {
        //        std::cout << "br_backward" << std::endl;
        auto [a, b, c, d] = bessel_jy(T(n), x);
        return a;
      };

    if constexpr(scalar_value<I> && scalar_value<T>)
    {
      //      std::cout << " kernel_bessel_j_int scalar scalar" << std::endl;
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
      if (n == 0)                                   return j0;        //cyl_bessel_j0(x);
      if (n == 1)                                   return factor*j1; //cyl_bessel_j1(x);
      if (is_eqz(x))                                return factor*x;   // as n >= 2
      if (n < eve::abs(x))                          return br_forward(n, x);      // forward recurrence
      if ((n > x * x / 4) || (x < 5))    return factor*br_small(n, x); // serie
      return br_backward(n, x);     // backward recurrence
    }
    else
    {
      T factor(1);
      auto isoddn = is_odd(n);
      auto nneg = is_ltz(n);
      factor = if_else(nneg, if_else(isoddn, T(-1), T(1)), factor);  // J_{-n}(z) = (-1)^n J_n(z)
      n = if_else(nneg, -n, n);

      auto xlt0 = is_ltz(x);
      factor *=  if_else(xlt0 && isoddn, T(-1), T(1));  // J_{n}(-z) = (-1)^n J_n(z)
      x = if_else(xlt0, -x, x);
      auto r = nan(as(x));
      auto isinfx = x == inf(as(x));
      r =  if_else(isinfx, zero(as(x)), allbits);
      x = if_else(isinfx, allbits, x);
      auto iseqzn = is_eqz(n);
      if (eve::any(iseqzn))
      {
        r = if_else(iseqzn, j0, r);
        x = if_else(iseqzn, allbits, x);
      }
      auto iseq1n = is_equal(n, one(as(n)));
      if (eve::any(iseq1n))
      {
        r = if_else(iseq1n, j1, r);
        x = if_else(iseq1n, allbits, x);
      }
      auto notdone = is_not_nan(x);

      if( eve::any(notdone) )
      {
        //std::cout << "br_large simd" << std::endl;
        notdone = next_interval(br_large,  notdone, asymptotic_bessel_large_x_limit(T(n), x), r, n, x);
        if( eve::any(notdone) )
        {
          //std::cout << "br_forward" << std::endl;
          notdone = next_interval(br_forward,  notdone, n < x, r, n, x);
          if( eve::any(notdone) )
          {
            //std::cout << "br_small" << std::endl;
            notdone = next_interval(br_small,  notdone, (n > x * x / 4) || (x < 5), r, n, x);
            if( eve::any(notdone) )
            {
              //std::cout << "br_bacward" << std::endl;
              notdone = last_interval(br_backward,  notdone, r, n, x);
            }
          }
        }
      }
      return factor*r;
    }
  }

  template<floating_real_value I, floating_real_value T>
  EVE_FORCEINLINE auto  kernel_bessel_j_flt (I , T x) noexcept
  {
    EVE_ASSERT(eve::none(is_flint(nu)); "kernel_bessel_j_flt : some nu are floating integers");
    if(scalar_value<I>)
    {

    }
    else
    {
    }
    return x;
  }

}
