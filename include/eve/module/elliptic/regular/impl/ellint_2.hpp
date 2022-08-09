//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/elliptic/regular/ellint_rd.hpp>
#include <eve/module/elliptic/regular/ellint_rf.hpp>
#include <eve/module/elliptic/regular/ellint_rg.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

template<floating_real_value T>
EVE_FORCEINLINE T
ellint_2_(EVE_SUPPORTS(cpu_), T k) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto k2 = sqr(k);
    auto r  = 2 * ellint_rg(zero(as(k)), oneminus(k2), one(as(k)));
    return if_else(k2 == one(as(k)), one, r);
  }
  else return apply_over(ellint_2, k);
}

template<floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
ellint_2_(EVE_SUPPORTS(cpu_), T phi, U x) noexcept
{
  return arithmetic_call(ellint_2, phi, x);
}

template<floating_real_value T>
EVE_FORCEINLINE T
ellint_2_(EVE_SUPPORTS(cpu_), T phi0, T x) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    x        = eve::abs(x);
    auto phi = abs(phi0);
    // Carlson's algorithm works only for |phi| <= pi/2,
    // use the integrand's periodicity to normalize phi
    //
    T    rphi = rem(phi, pio_2(as(phi))); // rempio2 ?
    T    m    = nearest((phi - rphi) / pio_2(as(phi)));
    auto oddm = is_odd(m);
    m         = inc[oddm](m);
    T s       = if_else(oddm, mone, one(as(x)));
    rphi      = if_else(oddm, pio_2(as(phi)) - rphi, rphi);

    auto k2           = sqr(x);
    auto [sinp, cosp] = sincos(rphi);
    auto sinp2        = sqr(sinp);
    auto notdone      = sinp2 * k2 <= one(as(phi));
    auto c            = if_else(notdone, rec(sinp2), allbits);
    auto cm1          = sqr(cosp) * c; // c-1
    auto r =
        s
        * (oneminus(k2) * ellint_rf(cm1, c - k2, c)
           + k2 * (oneminus(k2)) * ellint_rd(cm1, c, c - k2) / 3 + k2 * sqrt(cm1 / (c * (c - k2))));
    auto testz = is_eqz(k2);
    auto test1 = k2 == one(as(k2));

    r         = if_else(testz, phi, r);
    r         = if_else(test1, sinp, r);
    auto mgt0 = is_nez(m) && notdone;
    if( eve::any(mgt0) )
    {
      m = if_else(test1 || testz, zero, m);
      r += m * ellint_2(x);
    }
    return copysign(r, phi);
  }
  else return apply_over(ellint_2, phi0, x);
}

}
