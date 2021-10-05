//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/add.hpp>
#include <eve/function/all.hpp>
#include <eve/function/any.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/gather.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/max.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/sub.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/real/math/detail/generic/workaround.hpp>
#include <eve/traits/alignment.hpp>

#include <bit>
#include <type_traits>

namespace eve::detail
{
 // up to 255*pi/4 ~200
  template<floating_real_value T> EVE_FORCEINLINE kumi::tuple<T, T, T>
  rempio2_half_circle(T const &xx) noexcept
  {
    using elt_t             = element_type_t<T>;
    if constexpr( std::is_same_v<elt_t, double> )
    {
      /* Reduce range of x to within PI/4 with abs (x) < pi/2. */
      static const double mp1 = -0x1.921FB58000000p0;   /*  -1.5707963407039642      */
      static const double mp2 = 0x1.DDE973C000000p-27;  /*  1.3909067564377153e-08  */
      static const double mp3 = -0x1.CB3B399D747F2p-55; /* -4.9789962505147994e-17  */
      auto                xn  = nearest(xx * twoopi(eve::as<double>()));
      auto                y   = fma(xn, mp2, fma(xn, mp1, xx));
      auto                n   = quadrant(xn);
      auto                da  = xn * mp3;
      auto                a   = y - da;
      da                      = (y - a) - da;

      return {n, a, da};
    }
    else if constexpr(std::is_same_v<elt_t,  float>)
    {
      auto x =  float64(xx);
      auto n =  nearest(x*twoopi(eve::as<double>()));
      auto dxr = fma(n, -pio_2(eve::as<double>()), x);
      return {quadrant(float32(n)), float32(dxr), T(0.0f)};
    }
  }

  // double use   x < 281474976710656 (2.81476710656e+14)
  /* float use   x < 0x1.7d4998p+38 (4.09404e+11) */
  template<floating_real_value T> EVE_FORCEINLINE auto
  rempio2_medium(T const &xx) noexcept
  {
    using elt_t             = element_type_t<T>;
    static const double mp1 = -0x1.921FB58000000p0;   /* -1.5707963407039642      */
    static const double mp2 = 0x1.DDE973C000000p-27;  /*  1.3909067564377153e-08  */
    static const double pp3 = -0x1.CB3B398000000p-55; /* -4.9789962314799099e-17  */
    static const double pp4 = 0x1.d747f23e32ed7p-83;  /*  1.9034889620193266e-25  */
    if constexpr( std::is_same_v<elt_t, double> )
    {
      auto xn  = nearest(xx * twoopi(eve::as<double>()));
      auto xn1 = (xn + 8.0e22) - 8.0e22;
      auto xn2 = xn - xn1;
      auto y   = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, xx))));
      auto n   = quadrant(xn);
      auto da  = xn1 * pp3;
      auto t   = y - da;
      da       = (y - t) - da;
      da       = fma(xn, pp4, fnma(xn2, pp3, da));
      auto a   = t + da;
      da       = (t - a) + da;

      return kumi::make_tuple(n, a, da);
    }
    else if constexpr( std::is_same_v<elt_t, float> )
    {
      auto x   = float64(xx);
      auto xn  = nearest(x * twoopi(eve::as<double>()));
      auto xn1 = (xn + 8.0e22) - 8.0e22;
      auto xn2 = xn - xn1;
      auto y   = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, x))));
      auto n   = float32(quadrant(xn));
      auto da  = xn1 * pp3;
      auto t   = y - da;
      da       = (y - t) - da;
      da       = fma(xn, pp4, fnma(xn2, pp3, da));
      auto a   = t + da;
      da       = (t - a) + da;
      auto fa  = float32(a);
      auto dfa = float32((a - float64(fa)) + da);
      if( eve::any(fa >= pio_4(eve::as<float>()) || fa < -pio_4(eve::as<float>())) )
      {
        auto [n1, fa1, dfa1] = rempio2_half_circle(fa);
        n                     = quadrant(n + n1);

        return kumi::make_tuple(n, fa1, dfa1);
      }
      return kumi::make_tuple(n, fa, dfa);
    }
  }

  template<floating_real_value T> EVE_FORCEINLINE kumi::tuple<T, T, T>
  rempio2_full_circle(T const &x) noexcept
  {
    using elt_t             = element_type_t<T>;
    using elt_t =  element_type_t<T>;
    elt_t mp1, mp2, mp3;
    /* Reduce range of x to within PI/4 with abs (x) < pi. */
    if constexpr(std::is_same_v<elt_t, double>)
    {
      mp1 = -0x1.921FB58000000p0;   /*  -1.5707963407039642     */
      mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
      mp3 = -0x1.CB3B399D747F2p-55; /* -4.9789962505147994e-17  */
      auto xn  = nearest(x * twoopi(eve::as<elt_t>()));
      auto y    = fma (xn, mp2, fma (xn, mp1, x));
      auto n    = quadrant(xn);
      auto da   = xn * mp3;
      auto  a   = y - da;
      da        = (y - a) - da;
      return {n, a, da};
    }
    else
    {
      mp1 = -0x1.921fb0p+00f;        /* -1.57079601e+00 // pio2_high */
      mp2 = -0x1.5110b4p-22f;        /* -3.13916473e-07 // pio2_mid  */
      mp3 = -0x1.846988p-48f;        /* -5.39030253e-15 // pio2_low */
      auto xn  = nearest(x * twoopi(eve::as<elt_t>()));
      auto y    = fma (xn, mp3, fma (xn, mp2, fma (xn, mp1, x)));
      return {quadrant(xn), y, zero(as(y))};
    }
  }

  template<floating_real_value T> EVE_FORCEINLINE  kumi::tuple<T, T, T>
  rempio2_big(T xx) noexcept
  {
    using elt_t             = element_type_t<T>;
    if ( eve::all(xx < Rempio2_limit(quarter_circle_type(), as(xx))) )
    {
      return {T(0), xx, T(0)};
    }
    auto xlerfl = (xx <= Rempio2_limit(half_circle_type(), as<elt_t>()));
    if( eve::all(xlerfl) )
    {
      return rempio2_half_circle(xx);
    }
    if( eve::all(xx < Rempio2_limit(full_circle_type(), as(xx))) )
    {
      return rempio2_full_circle(xx);
    }
    if ( eve::all(xx < Rempio2_limit(medium_type(), as(xx))) )
    {
      return rempio2_medium(xx);
    }
    if constexpr( std::is_same_v<elt_t, double> )
    {
      using i32_tl = struct{ int32_t lo; int32_t hi; };
      using i32_tb = struct{ int32_t hi; int32_t lo; };
      using i32_ts =  std::conditional_t<std::endian::native == std::endian::little, i32_tl, i32_tb>;
      using ui64_ts = std::uint64_t;
      using ui64_tv = as_wide_t<uint64_t, cardinal_t<T>>;
      using i32_tv  = as_wide_t<int32_t, fixed<2 * cardinal_v<T>>>;
      using i32_t =  std::conditional_t<scalar_value<T>, i32_ts, i32_tv>;
      using ui64_t=  std::conditional_t<scalar_value<T>, ui64_ts, ui64_tv>;

      constexpr auto alg = alignment_v<T>;
      alignas(alg) constexpr double toverp[75] = {
          /*  2/ PI base 24*/
          10680707.0, 7228996.0,  1387004.0,  2578385.0,  16069853.0, 12639074.0, 9804092.0,
          4427841.0,  16666979.0, 11263675.0, 12935607.0, 2387514.0,  4345298.0,  14681673.0,
          3074569.0,  13734428.0, 16653803.0, 1880361.0,  10960616.0, 8533493.0,  3062596.0,
          8710556.0,  7349940.0,  6258241.0,  3772886.0,  3769171.0,  3798172.0,  8675211.0,
          12450088.0, 3874808.0,  9961438.0,  366607.0,   15675153.0, 9132554.0,  7151469.0,
          3571407.0,  2607881.0,  12013382.0, 4155038.0,  6285869.0,  7677882.0,  13102053.0,
          15825725.0, 473591.0,   9065106.0,  15363067.0, 6271263.0,  9264392.0,  5636912.0,
          4652155.0,  7056368.0,  13614112.0, 10155062.0, 1944035.0,  9527646.0,  15080200.0,
          6658437.0,  6231200.0,  6832269.0,  16767104.0, 5075751.0,  3212806.0,  1398474.0,
          7579849.0,  6349435.0,  12618859.0, 4703257.0,  12806093.0, 14477321.0, 2786137.0,
          12875403.0, 9837734.0,  14528324.0, 13719321.0, 343717.0};
      double tm600 = Constant<double, 0x1a70000000000000ULL>(); /* 2 ^- 600 */
      double split = Constant<double, 0x41a0000002000000ULL>(); /* 2^27 + 1 */
      double hp0   = Constant<double, 0x3FF921FB54442D18ULL>(); /* 1.5707963267948966     */
      double hp1   = Constant<double, 0x3C91A62633145C07ULL>(); /* 6.123233995736766e-17  */
      double mp1   = Constant<double, 0x3FF921FB58000000ULL>(); /* 1.5707963407039642     */
      double mp2   = Constant<double, 0xBE4DDE9740000000ULL>(); /*-1.3909067675399456e-08 */
      T      x     = xx * tm600;
      T      t     = prevent_gcc_abusive_contract(x * split);
      T      x1    = t - (t - x);
      T      x2    = x - x1;
      T      sum(0);

      auto pass = [&toverp](auto x1, T &b1, T &bb1) {
        uint64_t t576 = 0x63f0000000000000ULL;                     /* 2 ^ 576  */
        double   tm24 = Constant<double, 0x3e70000000000000ULL>(); /* 2 ^- 24  */
        double   big  = Constant<double, 0x4338000000000000ULL>(); /*  6755399441055744      */
        double   big1 = Constant<double, 0x4358000000000000ULL>(); /* 27021597764222976      */
        T        sum(0);
        ui64_t   zero_lo(0xFFFFFFFF00000000ULL);
        i32_t k;
        i32_t tmp;
        T r[6];
        if constexpr(scalar_value<T>)
        {
          auto z = bit_and(zero_lo, bit_cast(x1, as<ui64_t>()));
          k.hi = int32_t(z >> 32);
          k.lo = int32_t(z & 0x00000000FFFFFFFFULL);
          k.hi =  bit_shr(k.hi, 20) & 2047;
          k.hi = eve::max((k.hi-450)/24, 0);

          tmp.hi = int32_t(t576 >> 32);
          tmp.lo = int32_t(t576 & 0x00000000FFFFFFFFULL);
          tmp.hi -= (k.hi*24 << 20);
        }
        else
        {
          k = bit_cast(bit_and(bit_cast(x1, as<ui64_t>()), zero_lo), as<i32_t>());
          k          = bit_shr(k, 20) & 2047;
          k          = eve::max((k - 450) / 24, 0);
          tmp   = bit_cast(ui64_t(t576), as<i32_t>());
          tmp -= (k * 24 << 20);
          k      = eve::max(k, zero(as(k)));
        }
        auto inds = (bit_cast(k, as<ui64_t>()) >> 32);
        auto tmp1 = bit_cast(tmp, as<T>());

        for( int i = 0; i < 6; ++i )
        {
          auto values = gather(eve::as_aligned(&toverp[0],cardinal_t<T>{}), inds);
          inds        = inc(inds);
          r[i]        = x1 * values * tmp1;
          tmp1 *= tm24;
        }
        T s;
        for( int i = 0; i < 3; ++i )
        {
          s = (r[i] + big) - big;
          sum += s;
          r[i] -= s;
        }
        T t(0);
        for( int i = 0; i < 6; ++i ) t += r[5 - i];
        T bb = (((((r[0] - t) + r[1]) + r[2]) + r[3]) + r[4]) + r[5];
        s    = (t + big) - big;
        sum += s;
        t -= s;
        T b = t + bb;
        bb  = (t - b) + bb;
        s   = (sum + big1) - big1;
        sum -= s;
        b1  = b;
        bb1 = bb;
        return sum;
      };

      T    b1, bb1, b2, bb2;
      auto sum1 = pass(x1, b1, bb1);
      auto sum2 = pass(x2, b2, bb2);
      sum       = sum1 + sum2;
      T    b    = b1 + b2;
      T    bb   = if_else(eve::abs(b1) > eve::abs(b2), (b1 - b) + b2, (b2 - b) + b1);
      auto test = eve::abs(b) > 0.5;
      auto z    = copysign(one(eve::as<T>()), b);
      b         = sub[test](b, z);
      sum       = add[test](sum, z);
      T s       = b + (bb + bb1 + bb2);
      t         = ((b - s) + bb) + (bb1 + bb2);
      b         = s * split;
      T t1      = b - (b - s);
      T t2      = s - t1;
      b         = s * hp0;
      bb        = (((t1 * mp1 - b) + t1 * mp2) + t2 * mp1) + (t2 * mp2 + s * hp1 + t * hp0);
      // fma ? TODO
      s = b + bb;
      t = (b - s) + bb;
      s = if_else(is_not_finite(x), eve::allbits, s);
      s = if_else(xx < Rempio2_limit(quarter_circle_type(), as(xx)), xx, s);
      t = if_else(xx < Rempio2_limit(quarter_circle_type(), as(xx)), T(0), t);
      auto q = if_else(xx < Rempio2_limit(quarter_circle_type(), as(xx)),T(0), quadrant(sum));
      return  {q, s, t};
    }
    else if constexpr( std::is_same_v<elt_t, float> )
    {
      using ui_ts         = std::uint32_t;
      using wui_ts        = std::uint64_t;
      using  i_ts         = std::int64_t;
      using ui_tv         = as_wide_t<uint32_t, cardinal_t<T>>;
      using wui_tv        = as_wide_t<uint64_t, cardinal_t<T>>;
      using  i_tv         = as_wide_t< int64_t, cardinal_t<T>>;
      using i_t           = std::conditional_t<scalar_value<T>, i_ts, i_tv>;
      using ui_t          = std::conditional_t<scalar_value<T>, ui_ts, ui_tv>;
      using wui_t         = std::conditional_t<scalar_value<T>, wui_ts, wui_tv>;

      constexpr auto alg = alignment_v<ui_tv>;
      // Table with 4/PI to 192 bit precision.  To avoid unaligned accesses
      //   only 8 new bits are added per entry, making the table 4 times larger.
      alignas(alg) constexpr const uint32_t __inv_pio4[24] = {
        0xa2,       0xa2f9,     0xa2f983,   0xa2f9836e, 0xf9836e4e, 0x836e4e44,
        0x6e4e4415, 0x4e441529, 0x441529fc, 0x1529fc27, 0x29fc2757, 0xfc2757d1,
        0x2757d1f5, 0x57d1f534, 0xd1f534dd, 0xf534ddc0, 0x34ddc0db, 0xddc0db62,
        0xc0db6295, 0xdb629599, 0x6295993c, 0x95993c43, 0x993c4390, 0x3c439041};
      constexpr const double pi63 = 0x1.921FB54442D18p-62; /* 2PI * 2^-64.  */
      auto [sn, sr, dsr]          = rempio2_full_circle(xx);
      auto xi                     = bit_cast(xx, as<ui_t>());
      auto index                  = ((xi >> 26) & 15);
      auto arr0 = gather(eve::as_aligned(&__inv_pio4[0], cardinal_t<T>{}), index);
      auto arr4 = uint64(gather(eve::as_aligned(&__inv_pio4[0], cardinal_t<T>{}), index + 4));
      auto arr8 = uint64(gather(eve::as_aligned(&__inv_pio4[0], cardinal_t<T>{}), index + 8));

      auto shift  = ((xi >> 23) & 7);
      auto xii    = bit_or(bit_and(xi, 0xffffff), 0x800000);
      xi    = (xii <<  shift);

      auto xi64   = uint64(xi);
      auto res0   = uint64(xi * arr0);

      wui_t res1  = xi64*arr4;
      wui_t res2  = xi64*arr8;
      res0        = ((res2 >> 32) | (res0 << 32));
      res0 += res1;

      auto n = ((res0 + (1ULL << 61)) >> 62);
      res0   = res0 - (n << 62); // -= n << 62;
      auto tmp =  bit_cast(res0, as<i_t>());
      auto xx1  = float64(tmp);
      auto bn   = if_else(xlerfl, sn, float32(n));
      auto z    = xx1 * pi63;
      auto sr1  = float32(z);
      auto dsr1 = float32(z - float64(sr1));
      auto br   = if_else(xlerfl, sr, sr1);
      auto dbr  = if_else(xlerfl, dsr, dsr1);
      br        = if_else(is_not_finite(xx), eve::allbits, br);
      auto test = xx <= Rempio2_limit(full_circle_type(), as(xx));
      return {if_else(test, sn, bn), if_else(test, sr, br), if_else(test, dsr, dbr)};
    }
  }
}
