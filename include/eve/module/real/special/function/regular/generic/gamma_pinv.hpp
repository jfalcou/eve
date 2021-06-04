//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/normal_distribution.hpp>
#include <eve/function/lognormal_distribution.hpp>
#include <eve/function/diff/gamma_p.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/average.hpp>
#include <eve/function/none.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/next.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto gamma_pinv_(EVE_SUPPORTS(cpu_)
                              , T a
                              , U b) noexcept
  ->  decltype(arithmetic_call(gamma_pinv, a, b))
  {
    return arithmetic_call(gamma_pinv, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T gamma_pinv_(EVE_SUPPORTS(cpu_), T p, T k) noexcept
  requires has_native_abi_v<T>
  {
    if constexpr(std::is_same_v<T, float>)
    {
      return float32(gamma_pinv(float64(p), float64(k)));
    }
    p = if_else(is_ltz(p) || p > one(as(p)), allbits, p);
    auto iseqzp = is_eqz(p);
    auto iseq1p = p == one(as(p));
    auto x = if_else(iseq1p, inf(as(p)), if_else(iseqzp, zero(as(p)), allbits));
    logical<T> notdone(is_not_nan(p) && !iseqzp && !iseq1p);
    auto d = rec(9*k);
    auto y = oneminus(d + invcdf(normal_distribution_01<T>, oneminus(p)) * eve::sqrt(d));

    x = if_else(notdone, k*sqr(y)*y, x);
    auto x0 = x;
    int i = 10;
    if (eve::none(notdone)) return x;
    while(i)
    {
      auto dx = if_else(notdone, (gamma_p(x, k)-p)/diff(gamma_p)(x, k), zero);
      x -= dx;
      if (i < 7) notdone = notdone && is_not_less(abs(dx), 4*eps(as(x))*max(eve::abs(x), one(as(x))));
      if (eve::none(notdone)) return x;
      --i;
    }
    notdone =  notdone || is_ltz(y);
    x = if_else(notdone, eve::abs(x0), x);
    auto xlo = if_else(notdone, eve::min(x/2, zero(as(x))), x);
    auto xhi = if_else(notdone, eve::min(x*2, eve::valmax(as(x))), x);
    auto inl = ((gamma_p(xlo, k) > p)||(gamma_p(xhi, k) <  p)) && (xlo !=  xhi);
    while (eve::any(inl))
    {
      xlo = if_else(inl, eve::max(xlo/2, zero(as(x))), xlo);
      xhi  = if_else(inl, eve::min(xhi*2, eve::valmax(as(x))), xhi);
      inl = ((gamma_p(xlo, k) > p)||(gamma_p(xhi, k) <  p)) && (xlo !=  xhi);
    }
    auto xmed = average(xlo, xhi);
    while (eve::any(notdone))
    {
      auto test = (gamma_p(xmed, k) <  p);
      xlo = if_else(test, xmed, xlo);
      xhi = if_else(test, xhi, xmed);
      notdone = ulpdist(xlo, xhi) > 1;
      xmed = average(xlo, xhi);
    }
    xmed = if_else(iseq1p, inf(as(p)), if_else(iseqzp, zero(as(p)), xmed));
    return if_else(k == one(as(k)),  -eve::log1p(-p), xmed);
  }
}
