//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/bessel/regular/cyl_bessel_j0.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE T
cyl_bessel_y0_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  using elt_t = element_type_t<T>;
  if constexpr( scalar_value<T> )
  {
    if( x == 0 ) return minf(as(x));
    if( x == inf(as(x)) ) return zero(as(x));
    if( is_nan(x) ) return x;
  }
  using v_t     = element_type_t<T>;
  auto Pi       = eve::pi(as(x));
  auto j0opi    = cyl_bessel_j0(x) / Pi;
  auto evaluate = [j0opi](auto x, auto x1, auto x11, auto x12, auto P, auto Q)
  {
    T y      = sqr(x);
    T z      = 2 * log(x / x1) * j0opi;
    T r      = reverse_horner(y, P)/reverse_horner(y, Q);
    T factor = (x + x1) * ((x - x11 / 256) - x12);
    return fma(factor, r, z);
  };

  auto br_3 = [evaluate](auto x)
  {
    x                               = if_else(x <= T(3), x, zero);
    using A6 = kumi::result::generate_t<6, elt_t>;
    static const A6 P1 = {1.0723538782003176831e+11,
             -8.3716255451260504098e+09,
             2.0422274357376619816e+08,
             -2.1287548474401797963e+06,
             1.0102532948020907590e+04,
             -1.8402381979244993524e+01};
    static const A6 Q1 = {5.8873865738997033405e+11,
             8.1617187777290363573e+09,
             5.5662956624278251596e+07,
             2.3889393209447253406e+05,
             6.6475986689240190091e+02,
             1.0};
    constexpr v_t x1 = 8.9357696627916752158e-01, x11 = 2.280e+02, x12 = 2.9519662791675215849e-03;
    return evaluate(x, x1, x11, x12, P1, Q1);
  };

  auto br_5 = [evaluate](auto x)
  {
    constexpr v_t x2 = 3.9576784193148578684e+00, x21 = 1.0130e+03, x22 = 6.4716931485786837568e-04;
    using A7 = kumi::result::generate_t<7, elt_t>;
    static const A7 P2 = {-2.2213976967566192242e+13,
             -5.5107435206722644429e+11,
             4.3600098638603061642e+10,
             -6.9590439394619619534e+08,
             4.6905288611678631510e+06,
             -1.4566865832663635920e+04,
             1.7427031242901594547e+01};
    static const A7 Q2 = {4.3386146580707264428e+14,
             5.4266824419412347550e+12,
             3.4015103849971240096e+10,
             1.3960202770986831075e+08,
             4.0669982352539552018e+05,
             8.3030857612070288823e+02,
             1.0};
    return evaluate(x, x2, x21, x22, P2, Q2);
  };

  auto br_8 = [evaluate](auto x)
  {
    constexpr v_t x3 = 7.0860510603017726976e+00, x31 = 1.8140e+03, x32 = 1.1356030177269762362e-04;
    using A8 = kumi::result::generate_t<8, elt_t>;
    static const A8 P3 = {-8.0728726905150210443e+15,
             6.7016641869173237784e+14,
             -1.2829912364088687306e+11,
             -1.9363051266772083678e+11,
             2.1958827170518100757e+09,
             -1.0085539923498211426e+07,
             2.1363534169313901632e+04,
             -1.7439661319197499338e+01};
    static const A8 Q3 = {3.4563724628846457519e+17,
             3.9272425569640309819e+15,
             2.2598377924042897629e+13,
             8.6926121104209825246e+10,
             2.4727219475672302327e+08,
             5.3924739209768057030e+05,
             8.7903362168128450017e+02,
             1.0};
    return evaluate(x, x3, x31, x32, P3, Q3);
  };

  auto br_large = [Pi](auto x)
  {
    using A6 = kumi::result::generate_t<6, elt_t>;
    static const A6 PC     = {
      2.2779090197304684302e+04,
      4.1345386639580765797e+04,
      2.1170523380864944322e+04,
      3.4806486443249270347e+03,
      1.5376201909008354296e+02,
      8.8961548424210455236e-01
    };
    static const A6 QC     = {
      2.2779090197304684318e+04,
      4.1370412495510416640e+04,
      2.1215350561880115730e+04,
      3.5028735138235608207e+03,
      1.5711159858080893649e+02,
      1.0
    };
    static const A6 PS     = {
      -8.9226600200800094098e+01,
      -1.8591953644342993800e+02,
      -1.1183429920482737611e+02,
      -2.2300261666214198472e+01,
      -1.2441026745835638459e+00,
      -8.8033303048680751817e-03
    };
    static const A6 QS     = {
      5.7105024128512061905e+03,
      1.1951131543434613647e+04,
      7.2642780169211018836e+03,
      1.4887231232283756582e+03,
      9.0593769594993125859e+01,
      1.0
    };
    T                            y      = T(8) / x;
    T                            y2     = sqr(y);
    T                            rc     = reverse_horner(y2, PC)/reverse_horner(y2, QC);
    T                            rs     = reverse_horner(y2, PS)/reverse_horner(y2, QS);
    T                            factor = rsqrt(Pi * x);
    auto [sx, cx]                       = sincos(x);
    return factor * fma(y, rs * (cx + sx), rc * (sx - cx));
  };

  if constexpr( scalar_value<T> )
  {
    if( x <= T(3) ) return br_3(x);   // x in (0, 3]
    if( x <= T(5.5) ) return br_5(x); // x in (3, 5.5]
    if( x <= T(8) ) return br_8(x);   // x in (5.5, 8]
    return br_large(x);               // x in (8, \infty)
  }
  else
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto r       = nan(as(x));
      auto notdone = is_nltz(x);

      if( eve::any(notdone) )
      {
        notdone = next_interval(br_3, notdone, x <= T(3), r, x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_5, notdone, x <= T(5.5), r, x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_8, notdone, x <= T(8), r, x);
            if( eve::any(notdone) ) { notdone = last_interval(br_large, notdone, r, x); }
          }
        }
      }
      r = if_else(is_eqz(x), minf(as(x)), r);
      r = if_else(x == inf(as(x)), zero, r);
      return r;
    }
    else return apply_over(cyl_bessel_y0, x);
  }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_y0_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::cyl_bessel_y0, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_y0_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::cyl_bessel_y0), ts ...);
}
}
