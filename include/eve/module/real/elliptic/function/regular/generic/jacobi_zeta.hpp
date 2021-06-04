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
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/ellint_rj.hpp>
#include <eve/function/ellint_1.hpp>
#include <eve/function/negate.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqrt.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE T jacobi_zeta_(EVE_SUPPORTS(cpu_)
                              , T phi
                              , U k) noexcept
  -> decltype(arithmetic_call(jacobi_zeta, phi, k))
  {
    return arithmetic_call(jacobi_zeta, phi, k);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T jacobi_zeta_(EVE_SUPPORTS(cpu_)
                                , T phi
                                , T k) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto aphi = eve::abs(phi);
      auto [sinp, cosp] = sincos(aphi);
      auto s2 = sqr(sinp);
      auto k2 = sqr(k);
      auto kp = oneminus(k2);
      auto k2s2c = oneminus(k2*s2);
      auto e_rj = ellint_rj(zero(as(phi)), kp, one(as(phi)), k2s2c);
      auto e_1 = ellint_1(k);
      auto r = if_else(k2 == one(as(k)),  eve::signnz(cosp)*sinp
                      , k2*sinp*cosp*sqrt(k2s2c)*e_rj/(3*e_1));
      r =  if_else(aphi == pio_2(as(phi)), zero, r); //this is a guess of what the user wants pio_2 being not exact
      return negate(r, phi); ;
    }
    else
      return apply_over(jacobi_zeta, phi, k);
  }
}
