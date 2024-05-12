//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/bessel/detail/kernel_bessel_ij_small.hpp>
#include <eve/module/bessel/detail/kernel_bessel_jy.hpp>
#include <eve/module/bessel/detail/kernel_bessel_jy_large.hpp>
#include <eve/module/bessel/regular/cyl_bessel_y0.hpp>
#include <eve/module/bessel/regular/cyl_bessel_y1.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/as_element.hpp>

/////////////////////////////////////////////////////////////////////////////////
// These routines are detail of the computation of cylindrical bessel functions
// of the second kind and integer orders.
// They are not meant to be called directly,  as their validities depends on
// n and x ranges values which are not tested on entry.
// The inspiration is from boost math
/////////////////////////////////////////////////////////////////////////////////
namespace eve::detail
{

template<ordered_value I, floating_ordered_value T>
EVE_FORCEINLINE auto
kernel_bessel_y_large(I n, T x) noexcept
{
  return asymptotic_bessel_y_large_x_2(T(n), x);
}

template<ordered_value I, floating_ordered_value T>
EVE_FORCEINLINE auto
kernel_bessel_y_int_forward(I n, T x, T y0, T y1) noexcept
{
  auto prev    = y0; // cyl_bessel_y0(x);
  auto current = y1; // cyl_bessel_y1(x);
  int  k       = 1;
  T    factor(1);
  T    mult  = 2 * k / x;
  auto value = fms(mult, current, prev);
  prev       = current;
  current    = value;
  ++k;
  auto test = (mult > 1) && (eve::abs(current) > 1);
  if( eve::any(test) )
  {
    prev    = if_else(test, prev / current, prev);
    factor  = if_else(test, factor / current, factor);
    value   = if_else(test, value / current, value);
    current = if_else(test, one, current);
  }
  auto const maxn = maximum(n);
  while( k < maxn )
  {
    auto t0 = k < n;
    mult    = if_else(t0, 2 * k / x, zero);
    value   = if_else(t0, fms(mult, current, prev), value);
    prev    = current;
    current = value;
    ++k;
  }
  return value / factor;
}

template<integral_value I, floating_ordered_value T>
EVE_FORCEINLINE auto
kernel_bessel_y_int_forward(I nn, T x, T y0, T y1) noexcept
{
  if constexpr( simd_value<I> )
    return kernel_bessel_y_int_forward(convert(nn, as_element(y0)), x, y0, y1);
  else return kernel_bessel_y_int_forward(T(nn), x, y0, y1);
}

template<ordered_value I, floating_ordered_value T>
EVE_FORCEINLINE auto
kernel_bessel_y_medium(I n, T x) noexcept
{
  auto [j, jp, y, yp] = bessel_jy(T(n), x);
  return y;
}

template<floating_ordered_value T>
auto
kernel_bessel_yn_small_x(T n, T x)
{
  n = eve::max(n, T(2));
  EVE_ASSERT(eve::all(is_nltz(dec(n))),
             " kernel_bessel_yn_small_x : some n are less or equal to 1");
  auto xlt5   = x < T(5);
  x           = if_else(xlt5, x, one);
  n           = if_else(xlt5, n, one);
  using elt_t = element_type_t<T>;
  T y         = elt_t(0.25) * sqr(x);
  T log_xo_2  = eve::log(elt_t(0.5) * x);
  T log_nm1_f = eve::lfactorial(dec(n));
  T log_p1    = -n * log_xo_2 + log_nm1_f;
  T sum1(1);
  T k_t(1);

  for( int k = 1; k < maximum(n); ++k )
  {
    auto kltn = k < n;
    k_t       = if_else(kltn, k_t * (y / (k * (n - k))), k_t);
    sum1 += if_else(kltn, k_t, zero);
  }
  T    t1 = -eve::exp(log_p1) * sum1 * inv_pi(as(x));
  T    p2 = -exp(n * log_xo_2) * inv_pi(as(x));
  T    t2(0);
  auto nezp2 = is_nez(p2);
  if( eve::any(nezp2) )
  {
    constexpr int KMAX  = 20;
    T             dig_n = digamma(n);
    T             npk_f = eve::factorial(n);
    T             yk(1);
    T             k_f(1);
    T             dig_kp1   = T(-0.57721566490153286060651209008240243104215933593992);
    T             dig_npkp1 = dig_n + rec(n);
    T             sum2      = (dig_kp1 + dig_npkp1 - 2.0 * log_xo_2) / npk_f;
    for( elt_t k = 1; k < KMAX; k = inc(k) )
    {
      dig_kp1 += rec(k);
      dig_npkp1 += rec(n + k);
      k_f *= k;
      npk_f *= n + k;
      yk *= -y;
      k_t = yk * (dig_kp1 + dig_npkp1 - 2 * log_xo_2) / (k_f * npk_f);
      sum2 += k_t;
    }
    t2 = if_else(nezp2, p2 * sum2, t2);
  }
  return t1 + t2;
}

/////////////////////////////////////////////////////////////////////////
// bessel_y of integer order
template<ordered_value I, floating_ordered_value T>
EVE_FORCEINLINE auto
kernel_bessel_y_int_pos(I n, T x) noexcept
{
  EVE_ASSERT(eve::all(is_flint(n)), "kernel_bessel_y_int_pos : somme n are not floating integer");
  EVE_ASSERT(eve::all(is_nltz(x)), "kernel_bessel_y_int_pos : somme x are not positive");
  EVE_ASSERT(eve::all(is_nltz(n)), "kernel_bessel_y_int_pos : somme n are not positive");
  auto br_large   = [](auto n, auto x) { return kernel_bessel_y_large(n, x); };
  auto br_forward = [](auto n, auto x)
  {
    auto y0 = cyl_bessel_y0(x);
    auto y1 = cyl_bessel_y1(x);
    auto z  = kernel_bessel_y_int_forward(n, x, y0, y1);
    z       = if_else(is_eqz(n), y0, z);
    return if_else(n == one(as(n)), y1, z);
  };
  auto br_small  = [](auto n, auto x) { return kernel_bessel_yn_small_x(n, x); };
  auto br_medium = [](auto n, auto x) { return kernel_bessel_y_medium(n, x); };

  if constexpr( scalar_value<I> && scalar_value<T> )
  {
    if( is_ngez(x) ) return nan(as(x));
    if( is_eqz(x) ) return minf(as(x));
    if( x == inf(as(x)) ) return zero(as(x));
    if( asymptotic_bessel_large_x_limit(T(n), x) ) return br_large(T(n), x);
    if( n == 0 ) return cyl_bessel_y0(x);          // cyl_bessel_y0(x);
    if( n == 1 ) return cyl_bessel_y1(x);          // cyl_bessel_y1(x);
    if( n < eve::abs(x) ) return br_forward(n, x); // forward recurrence
    if( x < 5 ) return br_small(T(n), x);          // serie
    return br_medium(n, x);                        // medium recurrence
  }
  else
  {
    using elt_t = element_type_t<T>;
    auto r      = nan(as(x));
    auto isinfx = x == inf(as(x));
    r           = if_else(isinfx, zero(as(x)), allbits);
    x           = if_else(isinfx, mone, x);
    auto iseqzx = is_eqz(x);
    if( eve::any(iseqzx) ) { r = if_else(iseqzx, minf(as(x)), r); }

    auto notdone = is_nltz(x);
    x            = if_else(notdone, x, allbits);
    auto nn      = convert(n, as<elt_t>());
    if( eve::any(notdone) )
    {
      notdone = next_interval(cyl_bessel_y0, notdone, nn == 0, r, x);
      if( eve::any(notdone) )
      {
        notdone = next_interval(cyl_bessel_y1, notdone, nn == 1, r, x);
        if( eve::any(notdone) )
        {
          notdone =
              next_interval(br_large, notdone, asymptotic_bessel_large_x_limit(nn, x), r, nn, x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_forward, notdone, nn < x, r, nn, x);
            if( eve::any(notdone) )
            {
              notdone = next_interval(br_small, notdone, x < 5, r, nn, x);
              if( eve::any(notdone) ) { notdone = last_interval(br_medium, notdone, r, nn, x); }
            }
          }
        }
      }
    }
    return r;
  }
}

template<ordered_value I, floating_ordered_value T>
EVE_FORCEINLINE auto
kernel_bessel_y_int(I n, T x) noexcept
{
  x           = if_else(is_ltz(x), nan(as(x)), x);
  auto nlt0   = is_ltz(n);
  auto isoddn = is_odd(n);
  auto y      = kernel_bessel_y_int_pos(eve::abs(n), x);
  return if_else(isoddn && nlt0, -y, y);
}

template<floating_ordered_value T>
EVE_FORCEINLINE auto
kernel_bessel_y_flt(T n, T x) noexcept
{
  EVE_ASSERT(eve::none(is_flint(n)), "kernel_bessel_y_flt : some nu are floating integers");
  auto br_large = [](auto n, auto x) { return kernel_bessel_y_large(n, x); };

  auto br_medium = [](auto n, auto x) { return kernel_bessel_y_medium(n, x); };

  if constexpr( scalar_value<T> )
  {
    if( is_ltz(x) || is_ltz(n) ) return nan(as(x));
    if( is_eqz(x) ) return minf(as(x));
    if( x == inf(as(x)) ) return zero(as(x));
    if( asymptotic_bessel_large_x_limit(n, x) ) return br_large(n, x);
    return br_medium(n, x);
  }
  else
  {
    auto r       = nan(as(x));
    auto isinfx  = x == inf(as(x));
    r            = if_else(isinfx, zero(as(x)), allbits);
    x            = if_else(isinfx, mone, x);
    auto notdone = is_nltz(x);
    if( eve::any(notdone) )
    {
      notdone = next_interval(br_large, notdone, asymptotic_bessel_large_x_limit(n, x), r, n, x);
      if( eve::any(notdone) ) { notdone = last_interval(br_medium, notdone, r, n, x); }
    }
    return r;
  }
}

}
