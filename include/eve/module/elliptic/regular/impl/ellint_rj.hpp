//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/elliptic/regular/ellint_rc.hpp>
#include <eve/module/elliptic/regular/ellint_rd.hpp>
#include <eve/module/elliptic/regular/ellint_rf.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U, floating_real_value V, floating_real_value W>
EVE_FORCEINLINE auto
ellint_rj_(EVE_SUPPORTS(cpu_), T x, U y, V z, W p) noexcept requires
    compatible_values<T, U> && compatible_values<V, U> && compatible_values<V, W>
{
  return arithmetic_call(ellint_rj, x, y, z, p);
}

template<floating_real_value T, floating_real_value U, floating_real_value V, floating_real_value W>
EVE_FORCEINLINE auto
ellint_rj_(EVE_SUPPORTS(cpu_), raw_type const&, T x, U y, V z, W p) noexcept requires
    compatible_values<T, U> && compatible_values<V, U> && compatible_values<V, W>
{
  return arithmetic_call(raw(ellint_rj), x, y, z, p);
}

template<floating_real_value T>
EVE_FORCEINLINE T
ellint_rj_(EVE_SUPPORTS(cpu_), T x, T y, T z, T p) noexcept requires has_native_abi_v<T>
{
  auto r       = nan(as(x));
  auto notdone = is_nltz(x) && is_nltz(y) && is_nltz(z) && is_nez(p) && is_nez(x + y)
                 && is_nez(z + y) && is_nez(x + z);
  if( eve::any(notdone) )
  {
    auto br_pneg = [](auto x, auto y, auto z, auto p) // p < 0
    {
      auto cond_swap = [](auto cond, auto& a, auto& b)
      {
        auto aa = if_else(cond, a, b);
        auto bb = if_else(cond, b, a);
        a       = aa;
        b       = bb;
      };
      cond_swap(x < y, x, y);
      cond_swap(x < z, x, z);
      cond_swap(y > z, y, z);
      // now all(x <=  y) and all(y <=  z)
      auto q = -p;
      p      = fms(z, (x + y + q), x * y) / (z + q);
      auto v = (p - z) * ellint_rj(x, y, z, p);
      v -= 3 * ellint_rf(x, y, z);
      auto pq  = p * q;
      auto tmp = fma(x, y, pq);
      v += 3 * sqrt((x * y * z) / tmp) * ellint_rc(tmp, pq);
      v /= (z + q);
      return v;
    };
    notdone = next_interval(br_pneg, notdone, is_ltz(p), r, x, y, z, p);
    if( eve::any(notdone) )
    {
      auto br_eqxy = [](auto x, auto p) // (x == y) && (x == z)
      {
        auto rsqtx = rsqrt(x);
        return if_else(x == p, rsqtx / x, 3 * ellint_rc(x, p) - rsqtx / (x - p));
      };
      notdone = next_interval(br_eqxy, notdone, (x == y) && (x == z), r, x, p);
      if( eve::any(notdone) )
      {
        auto br_eqzp = [](auto x, auto y, auto z) //  (p == z)
        { return ellint_rd(x, y, z); };
        notdone = next_interval(br_eqzp, notdone, (z == p), r, x, y, z);
        if( eve::any(notdone) )
        {
          x            = if_else(notdone, x, one);
          y            = if_else(notdone, y, one);
          z            = if_else(notdone, z, one);
          p            = if_else(notdone, p, one);
          auto br_last = [](auto x, auto y, auto z, auto p) { return raw(ellint_rj)(x, y, z, p); };
          last_interval(br_last, notdone, r, x, y, z, p);
        }
      }
    }
  }
  return r;
}

template<floating_real_value T>
EVE_FORCEINLINE T
ellint_rj_(EVE_SUPPORTS(cpu_), raw_type const&, T x, T y, T z, T p) noexcept requires
    has_native_abi_v<T>
{
  auto xn    = x;
  auto yn    = y;
  auto zn    = z;
  auto pn    = p;
  auto an    = (x + y + z + 2 * p) / 5;
  auto a0    = an;
  auto delta = (p - x) * (p - y) * (p - z);
  auto q     = pow_abs(eps(as<T>()) / 5, -T(1) / 8)
           * (eve::max)((eve::max)(eve::abs(an - x), eve::abs(an - y)),
                        (eve::max)(eve::abs(an - z), eve::abs(an - p)));

  T fmn(one(as(x))); // 4^-n
  T rc_sum(zero(as(x)));

  for( unsigned n = 0; n < 30; ++n )
  {
    auto rx = sqrt(xn);
    auto ry = sqrt(yn);
    auto rz = sqrt(zn);
    auto rp = sqrt(pn);
    auto dn = (rp + rx) * (rp + ry) * (rp + rz);
    auto en = delta / dn;
    en /= dn;
    auto test = (en < -0.5) && (en > -1.5);
    auto rc1p = [](auto y)
    {
      auto r       = zero(as(y));
      auto notdone = true_(as(y)); //!= mone(as(y));
      if( eve::any(notdone) )
      {
        auto br_yltm1 = [](auto my) { return rsqrt(my) * ellint_rc(my, dec(my)); };
        notdone       = next_interval(br_yltm1, notdone, y < mone(as(y)), r, -y);
        if( eve::any(notdone) )
        {
          auto br_ygt0 = [](auto y)
          {
            return atan(sqrt(y)) * rsqrt(y);
            ;
          };
          notdone = next_interval(br_ygt0, notdone, is_gtz(y), r, y);
          if( eve::any(notdone) )
          {
            auto arg       = sqrt(-y);
            auto log1parg  = log1p(arg);
            auto br_ygtmhf = [arg, log1parg]()
            { return if_else(is_eqz(arg), T(1), (log1parg - log1p(-arg)) / (2 * arg)); };
            notdone = next_interval(br_ygtmhf, notdone, y > T(-0.5), r);
            if( eve::any(notdone) )
            {
              auto br_last = [arg, log1parg](auto y) { return log1parg * rsqrt(inc(y)) / arg; };
              last_interval(br_last, notdone, r, y);
            }
          }
        }
      }
      return r;
    };

    if( eve::any(test) )
    {
      //
      // occationally en ~ -1, we then have no means of calculating
      // rc(1, 1+en) without terrible cancellation error, so we
      // need to get to 1+en directly.  by substitution we have
      //
      // 1+e_0 = 1 + (p-x)*(p-y)*(p-z)/((sqrt(p) + sqrt(x))*(sqrt(p)+sqrt(y))*(sqrt(p)+sqrt(z)))^2
      //       = 2*sqrt(p)*(p+sqrt(x) * (sqrt(y)+sqrt(z)) + sqrt(y)*sqrt(z)) / ((sqrt(p) +
      //       sqrt(x))*(sqrt(p) + sqrt(y)*(sqrt(p)+sqrt(z))))
      //
      // and since this is just an application of the duplication formula for rj, the same
      // expression works for 1+en if we use x,y,z,p_n etc.
      // this branch is taken only once or twice at the start of iteration,
      // after than en reverts to it's usual very small values.
      //
      auto b   = 2 * rp * (pn + rx * (ry + rz) + ry * rz) / dn;
      auto r0  = ellint_rc(T(1), b);
      auto r1  = rc1p(en);
      auto tmp = if_else(test, r0, r1);
      rc_sum += fmn / dn * tmp;
    }
    else
    {
      auto r = rc1p(en);
      rc_sum += fmn / dn * r;
    }
    auto lambda = fma(rx, ry, fma(rx, rz, ry * rz));

    // from here on we move to n+1:
    an = (an + lambda) * T(0.25); // / 4;
    fmn /= 4;

    if( eve::all(fmn * q < an) ) break;

    xn = (xn + lambda) * T(0.25); // / 4;
    yn = (yn + lambda) * T(0.25); // / 4;
    zn = (zn + lambda) * T(0.25); // / 4;
    pn = (pn + lambda) * T(0.25); // / 4;
    delta *= T(0.015625);         // /= 64;
  }
  auto fmninvan = fmn * rec(an);
  auto xx       = (a0 - x) * fmninvan;
  auto yy       = (a0 - y) * fmninvan;
  auto zz       = (a0 - z) * fmninvan;
  p             = -(xx + yy + zz) / 2;
  auto p2       = sqr(p);
  auto xxyy     = xx * yy;
  auto e2       = xxyy + fma(xx, zz, fms(yy, zz, 3 * p2));
  auto p3       = p * p2;
  auto xxyyzz   = xxyy * zz;
  auto e3       = xxyyzz + 2 * e2 * p + 4 * p3;
  auto e4       = (2 * xxyyzz + e2 * p + 3 * p3) * p;
  auto e5       = xxyyzz * p2;
  auto e22      = sqr(e2);
  auto result   = fmninvan * rsqrt(an)
                * (1 - 3 * e2 / 14 + e3 / 6 + 9 * e22 / 88 - 3 * e4 / 22 - 9 * e2 * e3 / 52
                   + 3 * e5 / 26 - e2 * e22 / 16 + 3 * e3 * e3 / 40 + 3 * e2 * e4 / 20
                   + 45 * e22 * e3 / 272 - 9 * (e3 * e4 + e2 * e5) / 68);

  result += 6 * rc_sum;
  return result;
  //       auto r = nan(as(x));
  //       auto notdone = is_nltz(x) && is_nltz(y) && is_nltz(z) && is_nez(p) && is_nez( y + z) &&
  //       is_nez(z + x) && is_nez(y + x);
  //       // any parameterx, y, z nan or less than zero or more than one  zero or p zero implies
  //       nan auto br0 = [x, y, z](){return raw(ellint_rj)(x, y, z);}; last_interval(br0, notdone,
  //       r); return r;
}
}
