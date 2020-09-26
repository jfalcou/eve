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
#include <eve/constant/zero.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/expx2.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/prev.hpp>

#include <eve/function/is_nan.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/nbtrue.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/module/math/detail/generic/erf_kernel.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{

  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr T erfcx_(EVE_SUPPORTS(cpu_), D const &, T x) noexcept
      requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
  {
    /*
     * Based on: M. M. Shepherd and J. G. Laframboise, "Chebyshev Approximation of
     * (1+2x)exp(x^2)erfc x in 0 <= x < INF", Mathematics of Computation, Vol. 36,
     * No. 153, January 1981, pp. 249-253.
     *
     */
    if constexpr(scalar_value<T> && eve::platform::supports_invalids)
    {
      if (is_nan(x)) return x;
    }

    T a = eve::abs(x); // NaN-preserving absolute value computation
    using elt_t = element_type_t<T>;
    if constexpr(scalar_value<T>) if (is_infinite(a)) return zero(as<T>());
    constexpr auto isfloat = std::same_as<elt_t, float>;
    const T shift = if_else(isfloat, T(2), T(4));
    /* Compute q = (a-shift)/(a+shift) accurately. [0,INF) -> [-1,1] */
    T m = a - shift;
    T p = a + shift;
    auto r = rec(p);
    T q = m * r;
    T t = fnma (inc(q), shift, a);
    T e = fma (q, -a, t);
    q = fma (r, e, q);
    /* Approximate (1+2*a)*exp(a*a)*erfc(a) as p(q)+1 for q in [-1,1] */
    if constexpr(isfloat)
    {
      p =             0x1.f10000p-15f;  //  5.92470169e-5
      p = fma (p, q,  0x1.521cc6p-13f); //  1.61224554e-4
      p = fma (p, q, -0x1.6b4ffep-12f); // -3.46481771e-4
      p = fma (p, q, -0x1.6e2a7cp-10f); // -1.39681227e-3
      p = fma (p, q,  0x1.3c1d7ep-10f); //  1.20588380e-3
      p = fma (p, q,  0x1.1cc236p-07f); //  8.69014394e-3
      p = fma (p, q, -0x1.069940p-07f); // -8.01387429e-3
      p = fma (p, q, -0x1.bc1b6cp-05f); // -5.42122945e-2
      p = fma (p, q,  0x1.4ff8acp-03f); //  1.64048523e-1
      p = fma (p, q, -0x1.54081ap-03f); // -1.66031078e-1
      p = fma (p, q, -0x1.7bf5cep-04f); // -9.27637145e-2
      p = fma (p, q,  0x1.1ba03ap-02f); //  2.76978403e-1
    }
    else // isdouble
    {
      p =             0x1.edcad78fc8044p-31;  //  8.9820305531190140e-10
      p = fma (p, q,  0x1.b1548f14735d1p-30); //  1.5764464777959401e-09
      p = fma (p, q, -0x1.a1ad2e6c4a7a8p-27); // -1.2155985739342269e-08
      p = fma (p, q, -0x1.1985b48f08574p-26); // -1.6386753783877791e-08
      p = fma (p, q,  0x1.c6a8093ac4f83p-24); //  1.0585794011876720e-07
      p = fma (p, q,  0x1.31c2b2b44b731p-24); //  7.1190423171700940e-08
      p = fma (p, q, -0x1.b87373facb29fp-21); // -8.2040389712752056e-07
      p = fma (p, q,  0x1.3fef1358803b7p-22); //  2.9796165315625938e-07
      p = fma (p, q,  0x1.7eec072bb0be3p-18); //  5.7059822144459833e-06
      p = fma (p, q, -0x1.78a680a741c4ap-17); // -1.1225056665965572e-05
      p = fma (p, q, -0x1.9951f39295cf4p-16); // -2.4397380523258482e-05
      p = fma (p, q,  0x1.3be1255ce180bp-13); //  1.5062307184282616e-04
      p = fma (p, q, -0x1.a1df71176b791p-13); // -1.9925728768782324e-04
      p = fma (p, q, -0x1.8d4aaa0099bc8p-11); // -7.5777369791018515e-04
      p = fma (p, q,  0x1.49c673066c831p-8);  //  5.0319701025945277e-03
      p = fma (p, q, -0x1.0962386ea02b7p-6);  // -1.6197733983519948e-02
      p = fma (p, q,  0x1.3079edf465cc3p-5);  //  3.7167515521269866e-02
      p = fma (p, q, -0x1.0fb06dfedc4ccp-4);  // -6.6330365820039094e-02
      p = fma (p, q,  0x1.7fee004e266dfp-4);  //  9.3732834999538536e-02
      p = fma (p, q, -0x1.9ddb23c3e14d2p-4);  // -1.0103906603588378e-01
      p = fma (p, q,  0x1.16ecefcfa4865p-4);  //  6.8097054254651804e-02
      p = fma (p, q,  0x1.f7f5df66fc349p-7);  //  1.5379652102610957e-02
      p = fma (p, q, -0x1.1df1ad154a27fp-3);  // -1.3962111684056208e-01
      p = fma (p, q,  0x1.dd2c8b74febf6p-3);  //  2.3299511862555250e-01
    }

    /* Divide (1+p) by (1+2*a) ==> exp(a*a)*erfc(a) */
    T d = a + half(as<T>());
    r = rec(d);
    r *= half(as<T>());
    q = fma (p, r, r); // q = (p+1)/(1+2*a)
    t = q + q;
    e = (p - q) + fma (t, -a, T(1)); // residual: (p+1)-q*(1+2*a)
    r = fma (e, r, q);
//   if constexpr(std::same_as<D, pedantic_type> && eve::platform::supports_infinites)
//      r = if_else (a >= eve::prev(eve::valmax(as<T>())), eve::zero, r);
    r = if_else (a >= eve::valmax(as<T>())/2, rec(sqrt(pi(as(a))))/a, r);
    auto xpos = (x >= 0);
    if (all(xpos)) return r;
    /* Handle negative arguments: erfcx(x) = 2*exp(x*x) - erfcx(|x|) */

//     auto s = x * x;
//     d = fma (x, x, -s);
//     e = exp (s);
//     auto   r1 = e - r;
//     r1 = fma (e, d + d, r);
//     r1 = r + e;
//     r1 = if_else (e > Valmax<T>(), e,  r1); // 3.40282347e+38 // avoid creating NaN
//     r = if_else(xpos,  r,  r1);



    auto r1 = fms(T(2), expx2(x), r);
//    auto r1 = fms(T(2), exp(sqr(x)), r);
    r1 =  if_else(is_nan(r1), inf(as<T>()), r1);
    r = if_else(xpos, r, r1);
    return if_else (is_nan(x),  eve::allbits, r);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T erfcx_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    return erfcx(regular_type(), x);
  }

}
