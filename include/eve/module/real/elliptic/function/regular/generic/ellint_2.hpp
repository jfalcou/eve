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
#include <eve/function/average.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/ellint_rd.hpp>
#include <eve/function/ellint_rf.hpp>
#include <eve/function/ellint_rg.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_2_(EVE_SUPPORTS(cpu_)
                              , T k) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
//      auto notdone = eve::abs(k) < one(as(k));

//     if (abs(k) == 1)
//     {
//         return static_cast<T>(1);
//     }
      auto k2 = sqr(k);
      auto r = 2 * ellint_rg(zero(as(k)), oneminus(k2), one(as(k)));
      return if_else(k2 == one(as(k)), one, r);
    }
    else
      return apply_over(ellint_2, k);
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE T ellint_2_(EVE_SUPPORTS(cpu_)
                             , T phi
                             , U x) noexcept
  -> decltype(arithmetic_call(ellint_2, phi, x))
  {
    return arithmetic_call(ellint_2_, phi, x);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_2_(EVE_SUPPORTS(cpu_)
                             , T phi0
                             , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
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

      auto k2 = sqr(x);
      auto [sinp,  cosp] = sincos(rphi);
      auto sinp2 = sqr(sinp);
      auto notdone = sinp2*k2 <= one(as(phi));
      auto c = if_else(notdone, rec(sinp2), allbits);
      auto cm1 =  sqr(cosp)*c; // c-1
      auto r = s * (oneminus(k2)*ellint_rf(cm1, c-k2, c)
                    + k2*(oneminus(k2))*ellint_rd(cm1,c,c-k2)/3
                    + k2*sqrt(cm1/(c*(c-k2))));
      auto testz = is_eqz(k2);
      auto test1 = k2 == one(as(k2));

      r = if_else(testz, phi, r);
      r = if_else(test1, sinp, r);
      auto mgt0 =  is_nez(m) && notdone;
      if (eve::any(mgt0))
      {
        m =  if_else(test1 || testz, zero, m);
        r += m*ellint_2(x);
      }
      return copysign(r, phi);
    }
    else
      return apply_over(ellint_2, phi0, x);
  }

}
