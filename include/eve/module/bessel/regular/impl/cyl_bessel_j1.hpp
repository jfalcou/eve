//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE T
cyl_bessel_j1_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  using elt_t   = element_type_t<T>;
  auto br_large = [](auto x) // TODO specialize for float
  {
    using A7 = kumi::result::generate_t<7, elt_t>;
    constexpr A7 PC     = {-4.4357578167941278571e+06,
                 -9.9422465050776411957e+06,
                 -6.6033732483649391093e+06,
                 -1.5235293511811373833e+06,
                 -1.0982405543459346727e+05,
                 -1.6116166443246101165e+03,
                 0.0};
    constexpr A7 QC     = {-4.4357578167941278568e+06,
                 -9.9341243899345856590e+06,
                 -6.5853394797230870728e+06,
                 -1.5118095066341608816e+06,
                 -1.0726385991103820119e+05,
                 -1.4550094401904961825e+03,
                 1.0};
    constexpr A7 PS     = {3.3220913409857223519e+04,
                 8.5145160675335701966e+04,
                 6.6178836581270835179e+04,
                 1.8494262873223866797e+04,
                 1.7063754290207680021e+03,
                 3.5265133846636032186e+01,
                 0.0};
    constexpr A7 QS     = {7.0871281941028743574e+05,
                 1.8194580422439972989e+06,
                 1.4194606696037208929e+06,
                 4.0029443582266975117e+05,
                 3.7890229745772202641e+04,
                 8.6383677696049909675e+02,
                 1.0};
    T                              y      = 8 * rec(x);
    T                              y2     = sqr(y);
    auto                           rc     = reverse_horner(y2, PC)/reverse_horner(y2, QC);
    auto                           rs     = reverse_horner(y2, PS)/reverse_horner(y2, QS);
    auto                           factor = rsqrt(pi(as(x)) * x);
    auto [sx, cx]                         = sincos(x);
    auto value                            = factor * fma(y, rs * (sx + cx), rc * (sx - cx));
    return value;
  };
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( std::is_same_v<elt_t, float> )
    {
      auto br_2 = [](auto x)
      {
        const T              z  = sqr(x);
        using A5 = kumi::result::generate_t<5, elt_t>;
        constexpr A5 JP = {-4.878788132172128E-009f,
                 6.009061827883699E-007f,
                 -4.541343896997497E-005f,
                 1.937383947804541E-003f,
                 -3.405537384615824E-002f};

        return (z - 1.46819706421238932572E1f) * x * horner(z, JP);
      };

      auto br_8 = [](auto x)
      {
        auto                 q       = rec(x);
        auto                 w       = sqrt(q);
        using A8 = kumi::result::generate_t<8, elt_t>;
        constexpr A8 MO1     = {6.913942741265801E-002f,
                      -2.284801500053359E-001f,
                      3.138238455499697E-001f,
                      -2.102302420403875E-001f,
                      5.435364690523026E-003f,
                      1.493389585089498E-001f,
                      4.976029650847191E-006f,
                      7.978845453073848E-001f};
        constexpr auto       thpio4f = 2.35619449019234492885f; /* 3*pi/4 */
        constexpr A8 PH1     = {-4.497014141919556E+001f,
                      5.073465654089319E+001f,
                      -2.485774108720340E+001f,
                      7.222973196770240E+000f,
                      -1.544842782180211E+000f,
                      3.503787691653334E-001f,
                      -1.637986776941202E-001f,
                      3.749989509080821E-001f};
        auto                 p       = w * horner(q, MO1);
        w                            = sqr(q);
        auto xn                      = q * horner(w, PH1) - thpio4f;
        return p * cos(xn + x);
      };

      if constexpr( scalar_value<T> )
      {
        auto s = x < 0 ? -1 : 1;
        x      = abs(x);
        if( x == 0 ) return zero(as(x));          // x is 0
        if( x == inf(as(x)) ) return zero(as(x)); // x is infinite
        if( is_nan(x) ) return x;                 // x is nan
        if( x < 2 ) return s * br_2(x);           // x in (0, 2]
        if( x < 8 ) return s * br_8(x);           // x in (2, 8]
        return s * br_large(x);                   // x in (8, \infty)
      }
      else
      {
        auto xneg    = is_ltz(x);
        x            = abs(x);
        auto s       = if_else(xneg, mone, one(as(x)));
        auto r       = nan(as(x));
        auto notdone = is_gez(x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_2, notdone, x <= 2, r, x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_8, notdone, x <= 8, r, x);
            if( eve::any(notdone) ) { notdone = last_interval(br_large, notdone, r, x); }
          }
        }
        r = if_else(is_eqz(x) || (x == inf(as(x))), zero, r);
        return s * r;
      }
    }
    else
    {
      auto br_5 = [](auto x)
      {
        using A4 = kumi::result::generate_t<4, elt_t>;
        constexpr A4 RP = {
          -8.99971225705559398224E8,
          4.52228297998194034323E11,
          -7.27494245221818276015E13,
          3.68295732863852883286E15,
        };
        using A9 = kumi::result::generate_t<9, elt_t>;
        constexpr A9 RQ = {
          1.00000000000000000000E0,
          6.20836478118054335476E2,
          2.56987256757748830383E5,
          8.35146791431949253037E7,
          2.21511595479792499675E10,
          4.74914122079991414898E12,
          7.84369607876235854894E14,
          8.95222336184627338078E16,
          5.32278620332680085395E18,
        };
        auto  z  = sqr(x);
        auto  w  = horner(z, RP) / horner(z, RQ);
        elt_t Z1 = 1.46819706421238932572E1;
        elt_t Z2 = 4.92184563216946036703E1;
        return w * x * (z - Z1) * (z - Z2);
      };

      auto br_8 = [](auto x)
      {
        using A7 = kumi::result::generate_t<7, elt_t>;
        constexpr A7 PP = {
          7.62125616208173112003E-4,
          7.31397056940917570436E-2,
          1.12719608129684925192E0,
          5.11207951146807644818E0,
          8.42404590141772420927E0,
          5.21451598682361504063E0,
          1.00000000000000000254E0,
        };
        constexpr A7 PQ = {
          5.71323128072548699714E-4,
          6.88455908754495404082E-2,
          1.10514232634061696926E0,
          5.07386386128601488557E0,
          8.39985554327604159757E0,
          5.20982848682361821619E0,
          9.99999999999999997461E-1,
        };
        using A8 = kumi::result::generate_t<8, elt_t>;
        constexpr A8 QP = {
          5.10862594750176621635E-2,
          4.98213872951233449420E0,
          7.58238284132545283818E1,
          3.66779609360150777800E2,
          7.10856304998926107277E2,
          5.97489612400613639965E2,
          2.11688757100572135698E2,
          2.52070205858023719784E1,
        };
        constexpr A8 QQ = {
          1.00000000000000000000E0,
          7.42373277035675149943E1,
          1.05644886038262816351E3,
          4.98641058337653607651E3,
          9.56231892404756170795E3,
          7.99704160447350683650E3,
          2.82619278517639096600E3,
          3.36093607810698293419E2,
        };

        auto           w      = 5.0 * rec(x);
        auto           z      = sqr(w);
        auto           p      = horner(z, PP) / horner(z, PQ);
        auto           q      = horner(z, QP) / horner(z, QQ);
        constexpr auto thpio4 = 2.35619449019234492885; /* 3*pi/4 */
        auto           xn     = x - thpio4;
        auto [sxn, cxn]       = sincos(xn);
        p                     = fms(p, cxn, w * q * sxn);
        auto sq2opi           = T(.79788456080286535588);
        return if_else(x == inf(as(x)), zero, p * sq2opi * rsqrt(x));
      };

      if constexpr( scalar_value<T> )
      {
        auto s = x < 0 ? -1 : 1;
        x      = abs(x);
        if( x == 0 ) return zero(as(x));          // x is 0
        if( x == inf(as(x)) ) return zero(as(x)); // x is infinite
        if( is_nan(x) ) return x;                 // x is nan
        if( x < 5 ) return s * br_5(x);           // x in (0, 5]
        if( x < 8 ) return s * br_8(x);           // x in (5, 8]
        return s * br_large(x);                   // x in (8, \infty)
      }
      else
      {
        auto xneg    = is_ltz(x);
        x            = abs(x);
        auto s       = if_else(xneg, mone, one(as(x)));
        auto r       = nan(as(x));
        auto notdone = is_gez(x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_5, notdone, x <= T(5), r, x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_8, notdone, x <= T(8), r, x);
            if( eve::any(notdone) ) { notdone = last_interval(br_large, notdone, r, x); }
          }
        }
        r = if_else(is_eqz(x) || (x == inf(as(x))), zero, r);
        return s * r;
      }
    }
  }
  else return apply_over(eve::cyl_bessel_j1, x);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_j1_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::cyl_bessel_j1, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
cyl_bessel_j1_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::cyl_bessel_j1), ts ...);
}
}
