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

#include <eve/detail/hz_device.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/normal_distribution.hpp>
#include <eve/function/diff/gamma_p.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/average.hpp>
#include <eve/function/none.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/log.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>
#include <boost/math/special_functions/gamma.hpp>
#include <tts/tts.hpp>

namespace eve::detail
{

//   template<floating_value T, floating_value U>
//   EVE_FORCEINLINE  auto gamma_pinv_(EVE_SUPPORTS(cpu_)
//                               , T a
//                               , U b) noexcept
//   requires compatible_values<T, U>
//   {
//     return arithmetic_call(gamma_pinv, a, b);
//   }

  template<floating_real_value T>
  EVE_FORCEINLINE T gamma_pinv_(EVE_SUPPORTS(cpu_), T p, T k) noexcept
  requires has_native_abi_v<T>
  {
//    auto r = if_else(p == one(as(p)), inf(as(p)), allbits);
    p = if_else(is_ltz(p) || p > one(as(p)), allbits, p);
    auto d = rec(9*k);
    auto y = eve::max(oneminus(d + invcdf(normal_distribution_01<T>, oneminus(p)) * eve::sqrt(d)), eps(as(k)));
    auto x = if_else(is_eqz(p), zero, k*sqr(y)*y);

    logical<T> notdone(is_not_nan(p));
    int i = 10;
    while(eve::any(notdone))
    {
      auto dx = (gamma_p(x, k)-p)/diff(gamma_p)(x, k);
      x -= dx;
      notdone = is_not_less(abs(dx), 4*eps(as(x))*max(eve::abs(x), one(as(x))));
      if (eve::none(notdone)) return x;
      --i;
      if(!i) break;
    }
    auto xlo = if_else(notdone, eve::max(x*(1-10*eps(as(x))), zero(as(x))), x);
    auto xhi = if_else(notdone, eve::min(x*(1+10*eps(as(x))), eve::valmax(as(x))), x);
    auto inl = !is_lez((gamma_p(xlo, k)-p)*(gamma_p(xhi, k)-p)) && (xlo !=  xhi);
    while (eve::any(inl))
    {
      xlo = if_else(inl, eve::max(xlo*(1-10*eps(as(x))), zero(as(x))), xlo);
      xhi  = if_else(inl, eve::min(xhi*(1+10*eps(as(x))), eve::valmax(as(x))), xhi);
      inl = !is_ltz((gamma_p(xlo, k)-p)*(gamma_p(xhi, k)-p)) && (xlo !=  xhi);
    }
    auto xmed = average(xlo, xhi);
    while (eve::any(notdone))
    {
      auto test = !is_lez((gamma_p(xmed, k)-p)*(gamma_p(xhi, k)-p));
      xlo = if_else(test, xmed, xlo);
      xhi = if_else(test, xhi, xmed);
      notdone = (xhi-xlo) < 4*eps(as(x))*xhi;
      xmed = average(xlo, xhi);
    }
    return xmed;
  }
}
