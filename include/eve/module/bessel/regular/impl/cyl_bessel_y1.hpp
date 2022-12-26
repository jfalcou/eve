//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/bessel/regular/cyl_bessel_j1.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

template<floating_ordered_value T>
EVE_FORCEINLINE T
cyl_bessel_y1_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  using elt_t = element_type_t<T>;
  if constexpr( scalar_value<T> )
  {
    if( x == 0 ) return minf(as(x));
    if( x == inf(as(x)) ) return zero(as(x));
    if( is_ngez(x) ) return nan(as(x));
  }
  using v_t     = element_type_t<T>;
  auto Pi       = eve::pi(as(x));
  auto j1opi    = cyl_bessel_j1(x) / Pi;
  auto evaluate = [j1opi](auto x, auto x1, auto x11, auto x12, auto P, auto Q)
  {
    T y      = sqr(x);
    T z      = 2 * log(x / x1) * j1opi;
    T r      = reverse_horner(y, P)/reverse_horner(y, Q);
    T factor = (x + x1) * ((x - x11 / 256) - x12) / x;
    return fma(factor, r, z);
  };

  auto br_4 = [evaluate](auto x)
  {
    using A7 = kumi::result::generate_t<7, elt_t>;
    static const A7 P1 = {4.0535726612579544093e+13,
             5.4708611716525426053e+12,
             -3.7595974497819597599e+11,
             7.2144548214502560419e+09,
             -5.9157479997408395984e+07,
             2.2157953222280260820e+05,
             -3.1714424660046133456e+02};
    static const A7 Q1 = {3.0737873921079286084e+14,
             4.1272286200406461981e+12,
             2.7800352738690585613e+10,
             1.2250435122182963220e+08,
             3.8136470753052572164e+05,
             8.2079908168393867438e+02,
             1.0};
    constexpr v_t x1 = 2.1971413260310170351e+00, x11 = 5.620e+02, x12 = 1.8288260310170351490e-03;
    return evaluate(x, x1, x11, x12, P1, Q1);
  };

  auto br_8 = [evaluate](auto x)
  {
    constexpr v_t x2 = 5.4296810407941351328e+00, x21 = 1.3900e+03,
                  x22               = -6.4592058648672279948e-06;
    using A9 = kumi::result::generate_t<9, elt_t>;
    static const A9 P2 = {1.1514276357909013326e+19,
             -5.6808094574724204577e+18,
             -2.3638408497043134724e+16,
             4.0686275289804744814e+15,
             -5.9530713129741981618e+13,
             3.7453673962438488783e+11,
             -1.1957961912070617006e+09,
             1.9153806858264202986e+06,
             -1.2337180442012953128e+03};
    static const A9 Q2 = {5.3321844313316185697e+20,
             5.6968198822857178911e+18,
             3.0837179548112881950e+16,
             1.1187010065856971027e+14,
             3.0221766852960403645e+11,
             6.3550318087088919566e+08,
             1.0453748201934079734e+06,
             1.2855164849321609336e+03,
             1.0};
    return evaluate(x, x2, x21, x22, P2, Q2);
  };

  auto br_large = [Pi](auto x)
  {
    using A7 = kumi::result::generate_t<7, elt_t>;
    static const A7 PC = {
      -4.4357578167941278571e+06,
      -9.9422465050776411957e+06,
      -6.6033732483649391093e+06,
      -1.5235293511811373833e+06,
      -1.0982405543459346727e+05,
      -1.6116166443246101165e+03,
      0.0
    };
    static const A7 QC     = {
      -4.4357578167941278568e+06,
      -9.9341243899345856590e+06,
      -6.5853394797230870728e+06,
      -1.5118095066341608816e+06,
      -1.0726385991103820119e+05,
      -1.4550094401904961825e+03,
      1.0
    };
    static const A7 PS     = {
      3.3220913409857223519e+04,
      8.5145160675335701966e+04,
      6.6178836581270835179e+04,
      1.8494262873223866797e+04,
      1.7063754290207680021e+03,
      3.5265133846636032186e+01,
      0.0
    };
    static const A7 QS     = {
      7.0871281941028743574e+05,
      1.8194580422439972989e+06,
      1.4194606696037208929e+06,
      4.0029443582266975117e+05,
      3.7890229745772202641e+04,
      8.6383677696049909675e+02,
      1.0
    };
    T                            y      = T(8) / x;
    T                            y2     = sqr(y);
    T                            rc     = reverse_horner(y2, PC)/reverse_horner(y2, QC);
    T                            rs     = reverse_horner(y2, PS)/reverse_horner(y2, QS);
    T                            factor = rsqrt(Pi * x);
    auto [sx, cx]                       = sincos(x);
    return factor * fms(y, rs * (sx - cx), rc * (sx + cx));
  };

  if constexpr( scalar_value<T> )
  {
    if( x <= T(4) ) return br_4(x); // x in (0, 4]
    if( x <= T(8) ) return br_8(x); // x in (4, 8]
    return br_large(x);             // x in (8, \infty)
  }
  else
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto r       = nan(as(x));
      auto notdone = is_nltz(x);

      if( eve::any(notdone) )
      {
        notdone = next_interval(br_4, notdone, x <= T(4), r, x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_8, notdone, x <= T(8), r, x);
          if( eve::any(notdone) ) { notdone = last_interval(br_large, notdone, r, x); }
        }
      }
      r = if_else(is_eqz(x), minf(as(x)), r);
      r = if_else(x == inf(as(x)), zero, r);
      return r;
    }
    else return apply_over(cyl_bessel_y1, x);
  }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_y1_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::cyl_bessel_y1, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_y1_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::cyl_bessel_y1), ts ...);
}
}
