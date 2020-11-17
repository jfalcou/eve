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

#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/all.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/gather.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/max.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/two_split.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/module/math/detail/generic/workaround.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <type_traits>
#include <tuple>
#include <bit>

namespace eve::detail
{

 // up to 255*pi/4 ~200
  template <floating_real_scalar_value T>
  EVE_FORCEINLINE auto  rempio2_small(T const &xx) noexcept
  {
    if constexpr(std::is_same_v<T,  double>)
    {
      /* Reduce range of x to within PI/2 with abs (x) < 105414350. */
      static const double mp1 = -0x1.921FB58000000p0;   /*  -1.5707963407039642      */
      static const double mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
      static const double mp3 = -0x1.CB3B399D747F2p-55; /* -4.9789962505147994e-17  */
      auto xn =  nearest(xx*twoopi(eve::as<double>()));
      auto y  =  fma(xn, mp2, fma(xn, mp1, xx));
      auto n = quadrant(xn);
      auto da = xn * mp3;
      auto a = y - da;
      da = (y - a) - da;
      return std::make_tuple(n, a, da);
    }
    else if constexpr(std::is_same_v<T,  float>)
    {
      static constexpr double pi_inv = 0x1.45F306DC9C883p+23;
      double r = xx * pi_inv;
      int32_t  n = ((int32_t)r + 0x800000) >> 24;
      double xr = xx - n * pio_2(eve::as<double>());
      float dxr = xr-float(xr);
      float fn =  n&3;
      return std::make_tuple(fn, float(xr), dxr);
    }
  }

  //double use   x < 281474976710656 (2.81476710656e+14)
  /* float use   x < 0x1.7d4998p+38 (4.09404e+11) */
  template <floating_real_scalar_value T>
  EVE_FORCEINLINE auto rempio2_medium(T const &xx) noexcept
  {
    if constexpr(std::is_same_v<T,  double>)
    {
      static const double mp1 = -0x1.921FB58000000p0;   /* -1.5707963407039642      */
      static const double mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
      static const double pp3 = -0x1.CB3B398000000p-55; /* -4.9789962314799099e-17  */
      static const double pp4 =  0x1.d747f23e32ed7p-83; /*  1.9034889620193266e-25  */

      auto xn =  nearest(xx*twoopi(eve::as<double>()));
      auto xn1 = (xn + 8.0e22) - 8.0e22;
      auto xn2 = xn - xn1;
      auto y = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, xx))));
      auto n = quadrant(xn);
      auto da = xn1 * pp3;
      auto t = y - da;
      da = (y - t) - da;
      da = fma(xn, pp4, fnma(xn2, pp3, da));
      auto a = t + da;
      da = (t - a) + da;
      return std::make_tuple(n, a, da);
    }
    else if constexpr(std::is_same_v<T,  float>)
    {
      static const double mp1 = -0x1.921FB58000000p0;   /* -1.5707963407039642      */
      static const double mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
      static const double pp3 = -0x1.CB3B398000000p-55; /* -4.9789962314799099e-17  */
      static const double pp4 =  0x1.d747f23e32ed7p-83; /*  1.9034889620193266e-25  */
      auto x  = float64(xx);
      auto xn =  nearest(x*twoopi(eve::as<double>()));
      auto xn1 = (xn + 8.0e22) - 8.0e22;
      auto xn2 = xn - xn1;
      auto y = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, x))));
      auto n = float32(quadrant(xn));
      auto da = xn1 * pp3;
      auto t = y - da;
      da = (y - t) - da;
      da = fma(xn, pp4, fnma(xn2, pp3, da));
      auto a = t + da;
      da = (t - a) + da;
      auto fa = float32(a);
      auto dfa = float32((a- float64(fa))+da);
      if (fa >= pio_4(eve::as<float>()) || fa < - pio_4(eve::as<float>()))
      {
        T n1;
        std::tie(n1, fa, dfa) = rempio2_small(fa);
        n =quadrant(n+n1);
        return std::make_tuple(n, fa, dfa);
      }
      return std::make_tuple(n, fa, dfa);
    }
  }

  template<floating_real_scalar_value T>
  EVE_FORCEINLINE auto rempio2_big(T const &xx) noexcept
  {
    if (is_not_finite(xx)) return std::make_tuple(T(0), nan(eve::as<T>()),T(0));
    if (xx < Rempio2_limit(restricted_type(), as(xx)))
    {
      return std::make_tuple(T(0), xx, T(0));
    }
    if( xx <= Rempio2_limit(small_type(), as(xx)))
    {
      return rempio2_small(xx);
    }
    if (xx < Rempio2_limit(medium_type(), as(xx)))
    {
      return rempio2_medium(xx);
    }
    if constexpr(std::is_same_v<T, double>)
    {
      // for x less than 9.23297861778572e-128 (smallestposval*2^600)
      //   and greater than 2.20131364292740010161e-134  the following routine is incorrect
      //   because  of the denormality of x*2^600
      //   it should return x inchanged in second output and  0 in third one. this is done by
      //   the restricted call
      double tm600 = Constant<double, 0x1a70000000000000ULL>(); /* 2 ^- 600 */
      double split = Constant<double, 0x41a0000002000000ULL>(); /* 2^27 + 1 */
      double hp0   = Constant<double, 0x3FF921FB54442D18ULL>(); /* 1.5707963267948966     */
      double hp1   = Constant<double, 0x3C91A62633145C07ULL>(); /* 6.123233995736766e-17  */
      double mp1   = Constant<double, 0x3FF921FB58000000ULL>(); /* 1.5707963407039642     */
      double mp2   = Constant<double, 0xBE4DDE9740000000ULL>(); /*-1.3909067675399456e-08 */
      double x     = xx * tm600;
      double t     = prevent_gcc_abusive_contract(x * split);
      double x1    = t - (t - x);
      double x2    = x - x1;

      auto pass = [](double x1, double& b1,  double& bb1) noexcept
        {
          constexpr double toverp[75] = {
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
          using i32_tl = struct{ int32_t lo; int32_t hi; };
          using i32_tb = struct{ int32_t hi; int32_t lo; };
          using i32_t =  std::conditional_t<std::endian::native == std::endian::little, i32_tl, i32_tb>;
          using ui64_t = std::uint64_t;
          uint64_t  t576 = 0x63f0000000000000ULL;                      /* 2 ^ 576  */
          double    tm24 = Constant<double, 0x3e70000000000000ULL>();  /* 2 ^- 24  */
          double     big = Constant<double, 0x4338000000000000ULL>();  /*  6755399441055744      */
          double    big1 = Constant<double, 0x4358000000000000ULL>();  /* 27021597764222976      */
          double sum(0);
          ui64_t zero_lo(0xFFFFFFFF00000000ULL);
          auto z = bit_and(zero_lo, bit_cast(x1, as<ui64_t>()));
          i32_t k;
          k.hi = int32_t(z >> 32);
          k.lo = int32_t(z & 0x00000000FFFFFFFFULL);
          k.hi =  bit_shr(k.hi, 20) & 2047;
          k.hi = eve::max((k.hi-450)/24, 0);

          i32_t tmp;
          tmp.hi = int32_t(t576 >> 32);
          tmp.lo = int32_t(t576 & 0x00000000FFFFFFFFULL);
          tmp.hi -= shl(k.hi*24, 20);

          double gor = bit_cast(tmp, as<double>());
          double r[6];
          auto inds = shr(bit_cast(k, as<ui64_t>()), 32);
          for (int i=0;i<6;++i)
          {
            auto values = toverp[inds];
            inds = inc(inds);
            r[i] = x1*values*gor;
            gor *= tm24;
          }
          double s;
          for (int i=0;i<3;++i) {
            s=(r[i]+big)-big;
            sum+=s;
            r[i]-=s;
          }
          double t(0);
          for (int i=0;i<6;++i)  t+=r[5-i];
          double bb=(((((r[0]-t)+r[1])+r[2])+r[3])+r[4])+r[5];
          s=(t+big)-big;
          sum+=s;
          t-=s;
          double b=t+bb;
          bb=(t-b)+bb;
          s=(sum+big1)-big1;
          sum-=s;
          b1  = b;
          bb1 = bb;
          return sum;
        };

      double b1, bb1, b2, bb2;
      double sum1 = pass(x1, b1, bb1);
      double sum2 = pass(x2, b2, bb2);
      double sum =  sum1+sum2;
      double b=b1+b2;
      double bb = (eve::abs(b1)>eve::abs(b2))? (b1-b)+b2 : (b2-b)+b1;
      if (b > 0.5)
      {
        b-=1.0;
        sum+=1.0;
      }
      else if (b < -0.5)
      {
        b+=1.0;
        sum-=1.0;
      }
      double s=b+(bb+bb1+bb2);
      t=((b-s)+bb)+(bb1+bb2);
      b=s*split;
      double t1=b-(b-s);
      double t2=s-t1;
      b=s*hp0;
      {
        auto z1 = t1*mp1;
        auto z2 = t1*mp2;
        auto z3 = t2*mp1;
        auto z4 = t2*mp2;
        auto z5 = s*hp1;
        auto z6 = t*hp0;
        bb = (((z1-b)+z2)+z3)+(z4+z5+z6);
      }

      s=b+bb;
      t=(b-s)+bb;
      return std::make_tuple(static_cast<double>((int) sum&3), s, t);
    }
    else if constexpr(std::is_same_v<T, float>)
    {
      // Table with 4/PI to 192 bit precision.  To avoid unaligned accesses
      //   only 8 new bits are added per entry, making the table 4 times larger.
      constexpr const uint32_t inv_pio4[24] =
        {
          0xa2,       0xa2f9,   0xa2f983,   0xa2f9836e,
          0xf9836e4e, 0x836e4e44, 0x6e4e4415, 0x4e441529,
          0x441529fc, 0x1529fc27, 0x29fc2757, 0xfc2757d1,
          0x2757d1f5, 0x57d1f534, 0xd1f534dd, 0xf534ddc0,
          0x34ddc0db, 0xddc0db62, 0xc0db6295, 0xdb629599,
          0x6295993c, 0x95993c43, 0x993c4390, 0x3c439041
        };
      constexpr const double pi63 = 0x1.921FB54442D18p-62;/* 2PI * 2^-64.  */
      auto xi =  bit_cast(xx, as_<uint32_t>());
      const uint32_t *arr = &inv_pio4[(xi >> 26) & 15];
      int shift = (xi >> 23) & 7;
      uint64_t n, res0, res1, res2;

      xi = (xi & 0xffffff) | 0x800000;
      xi <<= shift;

      res0 = xi * arr[0];
      res1 = (uint64_t)xi * arr[4];
      res2 = (uint64_t)xi * arr[8];
      res0 = (res2 >> 32) | (res0 << 32);
      res0 += res1;

      n = (res0 + (1ULL << 61)) >> 62;
      res0 -= n << 62;
      double xxx = (int64_t)res0;
      return std::make_tuple(static_cast<float>(n), static_cast<float>(xxx * pi63), 0.0f);
    }
  }
}
