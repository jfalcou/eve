//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/detail/erf_kernel.hpp>

namespace eve::detail
{

template<floating_real_value T, decorator D>
EVE_FORCEINLINE constexpr T
erfcx_(EVE_SUPPORTS(cpu_), D const&, T x) noexcept
    requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
{
  /*
   * Based on: M. M. Shepherd and J. G. Laframboise, "Chebyshev Approximation of
   * (1+2x)exp(x^2)erfc x in 0 <= x < INF", Mathematics of Computation, Vol. 36,
   * No. 153, January 1981, pp. 249-253.
   *
   */
  if constexpr( scalar_value<T> && eve::platform::supports_invalids )
  {
    if( is_nan(x) ) return x;
  }
  using elt_t     = element_type_t<T>;
  auto largelimit = []()
  {
    // for x greater than the value 1/(sqrt(pi)*x) ==  erfcx(x) at working precision
    if constexpr( std::is_same_v<elt_t, float> ) return 0x1.a919d2p+37; // 2.282242867200000e+11
    else return 0x1.fffffffffffffp+510;                                 // 6.703903964971298e+153
  };
  auto    ll        = largelimit();
  const T invsqrtpi = T(0.564189583547756286948079451560772585844050629329);
  T       a         = eve::abs(x);
  if constexpr( scalar_value<T> )
  {
    if( x == inf(as(x)) ) return zero(as(a));
    if( x > ll ) return invsqrtpi * rec(a);
    auto largeneglimit = []()
    {
      // for x less than the value erfcx(x) is inf at working precision
      if constexpr( std::is_same_v<elt_t, float> ) return -0x1.fffffcp+63; // -1.844674187468630e+19
      else return -0x1.ffffffffffffep+511; // -1.340780792994259e+154
    };
    if( x < largeneglimit() ) return inf(as(a));
  }
  constexpr auto isfloat = std::same_as<elt_t, float>;
  const T        shift   = if_else(isfloat, T(2), T(4));
  /* Compute q = (a-shift)/(a+shift) accurately. [0,INF) -> [-1,1] */
  T    m = a - shift;
  T    p = a + shift;
  auto r = rec(p);
  T    q = m * r;
  T    t = fnma(inc(q), shift, a);
  T    e = fma(q, -a, t);
  q      = fma(r, e, q);
  /* Approximate (1+2*a)*exp(a*a)*erfc(a) as p(q)+1 for q in [-1,1] */
  if constexpr( isfloat )
  {
    p = horn<T,
             0x3e8dd01d,
             0xbdbdfae7,
             0xbe2a040d,
             0x3e27fc56,
             0xbd5e0db6,
             0xbc034ca0,
             0x3c0e611b,
             0x3a9e0ebf,
             0xbab7153e,
             0xb9b5a7ff,
             0x39290e63,
             0x38788000>(q);
  }
  else // isdouble
  {
    p = horn<T,
             0x3fcdd2c8b74febf6ll,
             0xbfc1df1ad154a27fll,
             0x3f8f7f5df66fc349ll,
             0x3fb16ecefcfa4865ll,
             0xbfb9ddb23c3e14d2ll,
             0x3fb7fee004e266dfll,
             0xbfb0fb06dfedc4ccll,
             0x3fa3079edf465cc3ll,
             0xbf90962386ea02b7ll,
             0x3f749c673066c831ll,
             0xbf48d4aaa0099bc8ll,
             0xbf2a1df71176b791ll,
             0x3f23be1255ce180bll,
             0xbef9951f39295cf4ll,
             0xbee78a680a741c4all,
             0x3ed7eec072bb0be3ll,
             0x3e93fef1358803b7ll,
             0xbeab87373facb29fll,
             0x3e731c2b2b44b731ll,
             0x3e7c6a8093ac4f83ll,
             0xbe51985b48f08574ll,
             0xbe4a1ad2e6c4a7a8ll,
             0x3e1b1548f14735d1ll,
             0x3e0edcad78fc8044ll>(q);
  }

  /* Divide (1+p) by (1+2*a) ==> exp(a*a)*erfc(a) */
  T d = a + half(as<T>());
  r   = rec(d);
  r *= half(as<T>());
  q = fma(p, r, r); // q = (p+1)/(1+2*a)
  t = q + q;
  e = (p - q) + fma(t, -a, T(1)); // residual: (p+1)-q*(1+2*a)
  r = fma(e, r, q);
  if( eve::any(a > ll) ) r = if_else(a > ll, invsqrtpi * rec(a), r);
  auto xpos = (x >= 0);
  if( eve::all(xpos) ) return r;
  /* Handle negative arguments: erfcx(x) = 2*exp(x*x) - erfcx(|x|) */
  auto r1 = fms(T(2), expx2(x), r);
  r1      = if_else(is_nan(r1), inf(as<T>()), r1);
  r       = if_else(xpos, r, r1);
  return if_else(is_nan(x), eve::allbits, r);
}

template<floating_real_value T>
EVE_FORCEINLINE T
erfcx_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  return erfcx(regular_type(), x);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
erfcx_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::erfcx, t);
}
}
