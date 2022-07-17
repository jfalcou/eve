//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/erfc_inv.hpp>
#include <eve/module/special/regular/gamma_p.hpp>
#include <eve/module/special/regular/lgamma.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
common_compatible_t<T, U>
gamma_p_inv_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
{
  return arithmetic_call(gamma_p_inv, a, b);
}

template<floating_real_value T>
T
gamma_p_inv_(EVE_SUPPORTS(cpu_), T p, T k) noexcept requires has_native_abi_v<T>
{
  if constexpr( std::is_same_v<T, float> ) { return float32(gamma_p_inv(float64(p), float64(k))); }
  p                 = if_else(is_ltz(p) || p > one(as(p)), allbits, p);
  auto       iseqzp = is_eqz(p);
  auto       iseq1p = p == one(as(p));
  auto       x      = if_else(iseq1p, inf(as(p)), if_else(iseqzp, zero(as(p)), allbits));
  logical<T> notdone(is_not_nan(p) && !iseqzp && !iseq1p);
  auto       d   = rec(9 * k);
  auto       omp = oneminus(p);
  auto       y   = oneminus(d - sqrt_2(as(omp)) * erfc_inv(2 * omp) * eve::sqrt(d));

  x       = if_else(notdone, k * sqr(y) * y, x);
  auto x0 = x;
  int  i  = 10;
  if( eve::none(notdone) ) return x;
  auto dgamma_p = [](auto x, auto k) { return exp(dec(k) * log(x) - x - lgamma(k)); };
  while( i )
  {
    auto dx = if_else(notdone, (gamma_p(x, k) - p) / dgamma_p(x, k), zero);
    x -= dx;
    if( i < 7 )
      notdone = notdone && is_not_less(abs(dx), 4 * eps(as(x)) * max(eve::abs(x), one(as(x))));
    if( eve::none(notdone) ) return x;
    --i;
  }

  notdone  = notdone || is_ltz(y);
  x        = if_else(notdone, eve::abs(x0), x);
  auto xlo = if_else(notdone, eve::min(x / 2, zero(as(x))), x);
  auto xhi = if_else(notdone, eve::min(x * 2, eve::valmax(as(x))), x);
  auto inl = ((gamma_p(xlo, k) > p) || (gamma_p(xhi, k) < p)) && (xlo != xhi);
  while( eve::any(inl) )
  {
    xlo = if_else(inl, eve::max(xlo / 2, zero(as(x))), xlo);
    xhi = if_else(inl, eve::min(xhi * 2, eve::valmax(as(x))), xhi);
    inl = ((gamma_p(xlo, k) > p) || (gamma_p(xhi, k) < p)) && (xlo != xhi);
  }
  auto xmed = average(xlo, xhi);
  while( eve::any(notdone) )
  {
    auto gmp  = gamma_p(xmed, k);
    auto test = (gmp < p);
    xlo       = if_else(test, xmed, xlo);
    xhi       = if_else(test, xhi, xmed);
    notdone   = (ulpdist(xlo, xhi) > 1) && gmp != 0;
    xmed      = average(xlo, xhi);
  }
  xmed = if_else(iseq1p, inf(as(p)), if_else(iseqzp, zero(as(p)), xmed));
  return if_else(k == one(as(k)), -eve::log1p(-p), xmed);
}
}
