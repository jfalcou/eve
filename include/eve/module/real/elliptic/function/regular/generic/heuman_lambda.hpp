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
#include <eve/function/any.hpp>
#include <eve/function/ellint_rf.hpp>
#include <eve/function/ellint_rj.hpp>
#include <eve/function/ellint_1.hpp>
#include <eve/function/jacobi_zeta.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqrt.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE T heuman_lambda_(EVE_SUPPORTS(cpu_)
                              , T phi
                              , U k) noexcept
  -> decltype(arithmetic_call(heuman_lambda, phi, k))
  {
    return arithmetic_call(heuman_lambda, phi, k);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T heuman_lambda_(EVE_SUPPORTS(cpu_)
                                , T phi
                                , T k) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto test = eve::abs(phi) <= pio_2(as(k));
      auto k2 = sqr(k);
      auto kp = oneminus(k2);
      T r1(zero(as(k))), r2(zero(as(k)));
      if (eve::any(test))
      {
        auto [sinp, cosp] = sincos(phi);
        auto s2 = sqr(sinp);
        auto delta = sqrt(oneminus(kp*s2));
        r1 = kp * sinp * cosp / (delta * pio_2(as(k)));
        auto invsqrdelta = rec(sqr(delta));
        auto z1 =  ellint_rf(T(0), kp, T(1));
        auto z2 =  ellint_rj(zero(as(k)), kp, one(as(k)), oneminus(k2*invsqrdelta))*invsqrdelta/3;
        r1 *= fma(k2, z2, z1);
      }
      if (eve::any(!test))
      {
        auto rkp = sqrt(kp);
        auto  ratio = ellint_1(phi, rkp) / ellint_1(rkp);
        r2 = if_else(rkp == one(as(rkp)), inf(as(rkp)), ratio + ellint_1(k) * jacobi_zeta(phi, rkp) / pio_2(as(k)));
      }
      auto r = if_else(k2 > one(as(k2)), allbits, if_else(test, r1, r2));
      return if_else(phi == pio_2(as(phi)), one, r); //this is a guess about what user wants as pio_2 is not exact

    }
    else
      return apply_over(heuman_lambda, phi, k);
  }
}
