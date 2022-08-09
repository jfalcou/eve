//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/module/bessel/detail/kernel_bessel_jy.hpp>
#include <eve/module/bessel/regular/cyl_bessel_j0.hpp>
#include <eve/module/bessel/regular/cyl_bessel_j1.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>

/////////////////////////////////////////////////////////////////////////////////
// These routines are detail of the computation of cylindrical bessel functions
// of the first kind and second kind for integer orders and large x values.
//
// They are not meant to be called directly,  as their validities depends on
// n and x ranges values which are not tested on entry.
// The inspiration is from boost math
/////////////////////////////////////////////////////////////////////////////////
namespace eve::detail
{

///////////////////////////////////////////////////////////////////////////////
// large values routines
///////////////////////////////////////////////////////////////////////////////

template<floating_real_value T>
EVE_FORCEINLINE T
asymptotic_bessel_amplitude(T v, T x) noexcept
{
  // Calculate the amplitude of J(v, x) and Y(v, x) for large
  // x: see A&S 9.2.28.
  T s(1);
  T mu  = 4 * sqr(v);
  T txq = 2 * x;
  txq *= txq;
  auto mum1 = dec(mu);
  s += mum1 / (2 * txq);
  auto txq2 = sqr(txq);
  s += 3 * mum1 * (mu - 9) / (txq2 * 8);
  s += 15 * mum1 * (mu - 9) * (mu - 25) / (txq2 * txq * 8 * 6);

  return sqrt(s * 2 / (pi(as(x)) * x));
}

template<floating_real_value T>
EVE_FORCEINLINE T
asymptotic_bessel_phase_mx(T v, T x) noexcept
{
  //
  // Calculate the phase of J(v, x) and Y(v, x) for large x.
  // See A&S 9.2.29.
  // Note that the result returned is the phase less (x - PI(v/2 + 1/4))
  // which we'll factor in later when we calculate the sines/cosines of the result:
  //
  T    mu         = 4 * sqr(v);
  T    denom      = 4 * x;
  T    denom_mult = sqr(denom);
  auto mum1       = dec(mu);

  T s = mum1 / (2 * denom);
  denom *= denom_mult;
  s += mum1 * (mu - 25) / (6 * denom);
  denom *= denom_mult;
  auto mu2 = sqr(mu);
  s += mum1 * (mu2 - 114 * mu + 1073) / (5 * denom);
  denom *= denom_mult;
  s += mum1 * (5 * mu2 * mu - 1535 * mu2 + 54703 * mu - 375733) / (14 * denom);
  return s;
}

template<class T>
EVE_FORCEINLINE T
asymptotic_bessel_y_large_x_2(T v, T x) noexcept
{
  // See A&S 9.2.19.
  // Get the phase and amplitude:
  T ampl  = asymptotic_bessel_amplitude(v, x);
  T phase = asymptotic_bessel_phase_mx(v, x);
  //
  // Calculate the sine of the phase, using
  // sine/cosine addition rules to factor in
  // the x - PI(v/2 + 1/4) term not added to the
  // phase when we calculated it.
  //
  auto [sx, cx] = sincos(x);
  auto [si, ci] = sinpicospi(v / 2 + 0.25f);
  auto [sp, cp] = sincos(phase);
  return ampl * fma(sp, fma(cx, ci, sx * si), cp * fms(sx, ci, cx * si));
}

template<class T>
EVE_FORCEINLINE T
asymptotic_bessel_j_large_x_2(T v, T x) noexcept
{
  // See A&S 9.2.19.
  // Get the phase and amplitude:
  T ampl  = asymptotic_bessel_amplitude(v, x);
  T phase = asymptotic_bessel_phase_mx(v, x);
  //
  // Calculate the sine of the phase, using
  // sine/cosine addition rules to factor in
  // the x - PI(v/2 + 1/4) term not added to the
  // phase when we calculated it.
  //

  auto [sx, cx] = sincos(x);
  auto [si, ci] = sinpicospi(v / 2 + 0.25f);
  auto [sp, cp] = sincos(phase);
  return ampl * fms(cp, fma(cx, ci, sx * si), sp * fms(sx, ci, cx * si));
}

template<real_value N, floating_real_value T>
EVE_FORCEINLINE auto
asymptotic_bessel_large_x_limit(N v, T x) noexcept
{
  //
  // Determines if x is large enough compared to v to take the asymptotic
  // forms above.  From A&S 9.2.28 we require:  v < x * eps^1/8
  using elt_t = element_type_t<T>;
  if constexpr( integral_scalar_value<N> ) { return (eve::max)(v, 1) < x * 0.004f; }
  else if constexpr( integral_simd_value<N> )
  {
    return asymptotic_bessel_large_x_limit(convert(v, as<elt_t>()), x);
  }
  else
  {
    elt_t thresh = (sizeof(elt_t) == 8) ? 1.104854345603981e-02 : 0.1363135;
    return eve::max(T(eve::abs(v)), T(1)) < x * thresh;
  }
}
}
