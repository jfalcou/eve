//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/atanh.hpp>
#include <eve/function/average.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/ellint_rd.hpp>
#include <eve/function/ellint_rf.hpp>
#include <eve/function/ellint_rg.hpp>
#include <eve/function/ellint_rj.hpp>
#include <eve/function/ellint_1.hpp>
#include <eve/function/ellint_2.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/is_not_greater.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/tan.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE T ellint_3_(EVE_SUPPORTS(cpu_)
                             , U n
                             , T phi
                             , V k) noexcept
  -> decltype(arithmetic_call(ellint3, n, phi, k))
  {
    return arithmetic_call(ellint_3_, n, phi, k);
  }

 template<floating_real_value T>
  EVE_FORCEINLINE T ellint_3_(EVE_SUPPORTS(cpu_)
                              , T v
                              , T phi
                              , T k) noexcept
  -> decltype(arithmetic_call(llint_3, v, phi, k))
  {
    return ellint_3(v, phi, k, oneminus(v));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_3_(EVE_SUPPORTS(cpu_)
                              , T v
                              , T phi
                              , T k
                             ,  T vc) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto k2 = sqr(k);
      auto aphi = eve::abs(phi);
      auto sphi = sin(aphi);
      auto sphi2= sqr(sphi);
      auto notdone  = (k2*sphi2 < one(as(phi))) && (v*sphi2 <   one(as(phi)));
      auto r = nan(as(v));
      if (eve::any(notdone))
      {
        auto br_v0 =  [](auto phi, auto k) //v == 0
          {
            // A&S 17.7.18 & 19
            return if_else(is_eqz(k), phi, ellint_1(phi, k));
          };
        notdone = next_interval(br_v0, notdone, is_eqz(v), r, phi, k);
        if (eve::any(notdone))
        {
          auto vis1 = v == one(as(v));
          auto tanphi = tan(phi);
          auto br_v1k0 =  [tanphi]() // v == 1
            {
              return tanphi;
            };
          notdone = next_interval(br_v1k0, notdone, vis1 && is_eqz(k), r);
          if (eve::any(notdone))
          {
            auto br_v1 =  [sphi2, k2, tanphi](auto phi, auto k) //p < 0
              {
                auto result = sqrt(oneminus(k2*sphi2))*tanphi - ellint_2(phi, k);
                result /= oneminus(k2);
                return result + ellint_1(phi, k);
              };
            notdone = next_interval(br_v1, notdone, vis1, r, phi, k);
            if (eve::any(notdone))
            {
              auto br_philarge =  [aphi, vc](auto v,  auto phi,  auto k) //aphi*eps(as(aphi)) > one(as(aphi))
                {
                  return copysign(aphi*ellint_3(v, k, vc)/pio_2(as(phi)), phi);
                };
              notdone = next_interval(br_philarge, notdone, aphi*eps(as(aphi)) > one(as(aphi)), r, v, phi, k);
              if (eve::any(notdone))
              {
                 auto br_phigepio2 =  [aphi, vc](auto v,  auto phi,  auto k) //phi >= pi/2 || phi < 0
                {
                  auto rphi = rem(aphi, pio_2(as(aphi)));
                  auto m = nearest((aphi - rphi) /pio_2(as(aphi)));
                  auto test = is_nez(m) || (k >=   one(as(phi))); //not defined in this case
                  auto oddm = is_odd(m);
                  m = inc[oddm](m);
                  T s  = if_else(oddm, mone, one(as(k)));
                  rphi = if_else(oddm, pio_2(as(phi))-rphi, rphi);
                  auto result = s * ellint_3(v, rphi, k, vc);
                  result = add[is_gtz(m) && is_gtz(vc)](result, m * ellint_3(v, k, vc));
                  result = if_else(test, allbits, result);
                  return copysign(result, phi);
                };
                 notdone = next_interval(br_phigepio2, notdone, (phi >= pio_2(as(phi))) || (phi < 0) , r, v, phi, k);
                 if (eve::any(notdone))
                 {
                   auto br_k0 =  [tanphi](auto vc) ///k == 0
                     {
                       auto test =  is_gtz(vc);
                       auto vcr = sqrt(abs(vc));
                       auto arg = vcr*tanphi;
                       return if_else(test, atan(arg), average(log1p(arg), -log1p(-arg)))/vcr;
                     };
                   notdone = next_interval(br_k0, notdone, k == 0, r, vc);
                   if (eve::any(notdone))
                   {
                     auto br_vlt0k2le1 =  [k2, sphi2](auto phi, auto k, auto v, auto vc) /// (v < 0) && (k2 <= 1)
                       {
                         auto N = (k2 - v)/vc;
                         auto Nm1 = oneminus(k2)/vc;
                         auto p2 = sqrt(-v) * sqrt(N); // provision for very small p
                         auto delta = sqrt(oneminus(k2*sphi2));
                         auto result = ellint_3(N, phi, k, Nm1);
                         result *= -v/vc;
                         result *= dec(k2)/(v - k2);
                         result = if_else(N > k2, result, zero);
                         result = add[is_nez(k2)](result, ellint_1(phi, k)* k2 / (k2 - v));
                         auto t = -v/((k2 - v)*vc);
                         auto tmp = atan((p2 / 2) * sin(2 * phi) / delta);
                         result += tmp *if_else(t > valmin(as(phi)), sqrt(t), rsqrt(eve::abs(k2 - v)) * sqrt(eve::abs(v/vc)));
                         return result;
                       };
                     notdone = next_interval(br_vlt0k2le1, notdone, k == 0, r, phi, k, v, vc);
                     if (eve::any(notdone))
                     {
                       auto br_k1 =  [tanphi](auto phi, auto v, auto vc) /// (v >=  0) && (k == 1)
                         {
                           // See http://functions.wolfram.com/08.06.03.0013.01
                           auto sqrtv = sqrt(v);
                           auto [sinphi, cosphi] = sincos(phi);
                           auto result = sqrtv * atanh(sqrtv * sinphi) - log(rec(cosphi) + tanphi);
                           result /= -vc;
                           return result;
                         };
                       notdone = next_interval(br_k1, notdone, k == 1, r, phi, v, vc); // v is already >= 0 here
                       if (eve::any(notdone))
                       {
                         auto br_last =  [k2, sphi2, sphi](auto phi, auto v, auto vc) /// (v >=  0) && (k == 1)
                           {
                             // Carlson's algorithm works only for |phi| <= pi/2,
                             // by the time we get here phi should already have been
                             // normalised above.
                             //
                             //BOOST_ASSERT(fabs(phi) < constants::half_pi<T>());
                             //BOOST_ASSERT(phi >= 0);
                             auto cosphi = cos(phi);
                             auto xx = sqr(cosphi);
                             auto t = sphi2;
                             auto yy = oneminus(k2*t);
                             auto pp = if_else(v*t < T(0.5), oneminus(v*t), xx+vc*t);
                             auto zz = one(as(xx));
                             return sphi*(ellint_rf(xx, yy, zz) + v*t*ellint_rj(xx, yy, zz, pp)/3);
                           };
                         last_interval(br_last, notdone, r, phi, v, vc);
                       }
                     }
                   }
                 }
              }
            }
          }
        }
      }
      return r;
    }
    else
      return apply_over(ellint_3, v, phi, k);
  }

  template<floating_real_value T, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE T ellint_3_(EVE_SUPPORTS(cpu_)
                             , T n
                             , U k) noexcept
  {
    return arithmetic_call(ellint_3_, n, k);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_3_(EVE_SUPPORTS(cpu_)
                             , T v
                             , T k) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto k2 = sqr(k);
      auto notdone  = (k2 < one(as(k))) && (v < one(as(k)));
      auto r = nan(as(k));
      if (eve::any(notdone))
      {
        auto br_v0 =  [](auto k) //v == 0
          {
            // A&S 17.7.18 & 19
            return if_else(is_eqz(k), pio_2(as(k)), ellint_1(k));
          };
        notdone = next_interval(br_v0, notdone, is_eqz(v), r, k);
        if (eve::any(notdone))
        {
          auto br_vlt0 =  [k2](auto k, auto v) //v <  0
            {
              auto invvc = rec(oneminus(v));
              // Apply A&S 17.7.17:
              T N = (k2 - v)*invvc;
              T Nm1 = (1 - k2)*invvc;
              auto result = ellint_3(N, k, Nm1);
              // This next part is split in two to avoid spurious over/underflow:
              result *= -v*invvc;
              result *= oneminus(k2)/(k2 - v);
              result += ellint_1(k)*k2/(k2 - v);
              return result;
            };
          notdone = next_interval(br_vlt0, notdone, is_ltz(v), r, k, v);
          if (eve::any(notdone))
          {
            auto br_last =  [k2](auto v)
              {
                auto y(oneminus(k2));
                auto x(zero(as(y)));
                auto z(one(as(y)));
                auto p(oneminus(v));
                return ellint_rf(x, y, z) + v * ellint_rj(x, y, z, p) / 3;
              };
            last_interval(br_last, notdone, r, v);
          }
        }
      }
      return r;
    }
    else
      return apply_over(ellint_3, v, k);
  }

}
