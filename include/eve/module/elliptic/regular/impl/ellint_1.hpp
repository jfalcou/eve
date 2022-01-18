//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <eve/module/elliptic/regular/ellint_rf.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_1_(EVE_SUPPORTS(cpu_)
                             , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto xx = eve::abs(x);
      xx = if_else(xx > one(as(x)), allbits, xx);
      auto a = one(as(x));
      auto b = sqrt(oneminus(sqr(xx)));
      auto c = xx;
      while (eve::any((eve::abs(c) > eps(as(x)))))
      {
        auto an=average(a, b);
        auto bn=sqrt(a*b);
        c=average(a, -b);
        a=an;
        b=bn;
      }
      return pio_2(as(x))/b;
    }
    else
      return apply_over(ellint_1, x);
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE common_compatible_t<T, U> ellint_1_(EVE_SUPPORTS(cpu_)
                             , T phi
                             , U x) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(ellint_1, phi, x);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_1_(EVE_SUPPORTS(cpu_)
                             , T phi0
                             , T x) noexcept
  requires  has_native_abi_v<T>
  {
    x = eve::abs(x);
    auto phi =  abs(phi0);
    // Carlson's algorithm works only for |phi| <= pi/2,
    // use the integrand's periodicity to normalize phi
    //
    T rphi = rem(phi, pio_2(as(phi))); // rempio2 ?
    T m = nearest((phi - rphi) / pio_2(as(phi)));
    auto oddm = is_odd(m);
    m = inc[oddm](m);
    T s = if_else(oddm, mone, one(as(x)));
    rphi = if_else(oddm, pio_2(as(phi))-rphi, rphi);
    auto [sinp,  cosp] = sincos(rphi);
    sinp *= sinp;
    cosp *= cosp;
    auto notdone = sinp*sqr(x) < one(as(phi));

    auto c = if_else(notdone, rec(sinp), allbits);
    auto r = s*ellint_rf(cosp*c, c-sqr(x), c);
    auto xis1 = x == one(as(x));
    if (eve::any(xis1))
    {
      r = if_else(xis1, if_else(phi == pio_2(as(x)), inf(as(x)), asinh(tan(phi0))), r);
    }
    r = if_else(rphi < smallestposval(as(x)), s*rphi, r);
    auto mgt0 =  is_nez(m) && notdone;
    auto greatphi = eps(as(phi))*phi > one(as(phi))&&notdone;
    if (eve::any((mgt0||greatphi)&&notdone))
    {
      auto z = ellint_1(x);
      r += m*z;
      r = if_else(greatphi, phi*z/pio_2(as(x)), r);
    }
    return copysign(r, phi);
  }
}
