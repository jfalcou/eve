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
#include <eve/module/elliptic/regular/ellint_rd.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

template<floating_real_value T>
EVE_FORCEINLINE T
ellint_d_(EVE_SUPPORTS(cpu_), T k) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto r       = nan(as(k));
    auto t       = sqr(k);
    auto notdone = t < one(as(t));
    auto x(zero(as(k)));
    auto y = oneminus(t);
    auto z(one(as(k)));
    return if_else(notdone, if_else(t < eps(as(k)), pio_4(as(k)), ellint_rd(x, y, z) / 3), r);
  }
  else return apply_over(ellint_d, k);
}

template<floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
ellint_d_(EVE_SUPPORTS(cpu_), T phi, U x) noexcept
{
  return arithmetic_call(ellint_d, phi, x);
}

template<floating_real_value T>
EVE_FORCEINLINE T
ellint_d_(EVE_SUPPORTS(cpu_), T phi0, T k) noexcept requires has_native_abi_v<T>
{
  auto aphi    = eve::abs(phi0);
  auto r       = nan(as(aphi));
  auto notdone = is_finite(aphi); //&& test;
  r            = if_else(notdone, r, inf(as(phi0)));
  if( eve::any(notdone) )
  {
    auto br_philarge = [aphi](auto k) // aphi*eps(as(aphi)) > one(as(aphi))
    { return aphi * ellint_d(k) / pio_2(as(aphi)); };
    notdone = next_interval(br_philarge, notdone, aphi * eps(as(aphi)) > one(as(aphi)), r, k);
    if( eve::any(notdone) )
    {
      auto rphi         = rem(aphi, pio_2(as(aphi)));
      auto m            = nearest((aphi - rphi) / pio_2(as(aphi)));
      auto oddm         = is_odd(m);
      m                 = inc[oddm](m);
      T s               = if_else(oddm, mone, one(as(k)));
      rphi              = if_else(oddm, pio_2(as(phi0)) - rphi, rphi);
      auto [sinp, cosp] = sincos(rphi);
      T    c            = rec(sqr(sinp));
      T    cm1          = sqr(cosp) * c; // c - 1
      T    k2           = sqr(k);
      auto br_reg       = [c, cm1, k2, s, m](auto k)
      {
        auto z    = if_else(is_finite(c), s * ellint_rd(cm1, c - k2, c) / 3, zero);
        auto test = is_nez(m);
        if( eve::any(test) ) { return z + m * ellint_d(k); }
        else return z;
      };
      notdone = last_interval(br_reg, notdone, r, k);

      r = if_else(k2 * sinp * sinp > one(as(phi0)), allbits, r);
      r = if_else(is_eqz(phi0), zero, r);
    }
  }
  return copysign(r, phi0);
}


// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
ellint_d_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::ellint_d, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
ellint_d_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::ellint_d), ts ...);
}
}
