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
#include <eve/module/math.hpp>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U, floating_real_value V>
EVE_FORCEINLINE auto
ellint_rd_(EVE_SUPPORTS(cpu_),
           T x,
           U y,
           V z) noexcept requires compatible_values<T, U> && compatible_values<V, U>
{
  return arithmetic_call(ellint_rd, x, y, z);
}

template<floating_real_value T, floating_real_value U, floating_real_value V>
EVE_FORCEINLINE auto
ellint_rd_(EVE_SUPPORTS(cpu_), raw_type const&, T x, U y, V z) noexcept requires
    compatible_values<T, U> && compatible_values<V, U>
{
  return arithmetic_call(raw(ellint_rd), x, y, z);
}

template<floating_real_value T>
EVE_FORCEINLINE T
ellint_rd_(EVE_SUPPORTS(cpu_), raw_type const&, T x, T y, T z) noexcept requires has_native_abi_v<T>
{
  using elt_t = element_type_t<T>;
  T    xn     = x;
  T    yn     = y;
  T    zn     = z;
  T    an     = (x + y + T(3) * z) / 5;
  T    a0     = an;
  auto epsi   = pow_abs(elt_t(0.25) * eps(as(element_type_t<T>())), -1 / T(8));
  T    q = epsi * (eve::max)((eve::max)(eve::abs(an - xn), eve::abs(an - yn)), eve::abs(an - zn))
        * elt_t(1.2);
  T fn(one(as(x)));
  T rd_sum(zero(as(x)));

  // duplication
  unsigned k  = 0;
  T        hf = half(as(x));
  for( ; k < 30; ++k )
  {
    T root_x = eve::sqrt(xn);
    T root_y = eve::sqrt(yn);
    T root_z = eve::sqrt(zn);
    T lambda = root_x * root_y + root_x * root_z + root_y * root_z;
    rd_sum += fn / (root_z * (zn + lambda));
    an = average(an, lambda) * hf;
    xn = average(xn, lambda) * hf;
    yn = average(yn, lambda) * hf;
    zn = average(zn, lambda) * hf;
    q *= T(0.25);
    fn *= T(0.25);
    if( eve::all(q < eve::abs(an)) ) break;
  }

  T invan = rec(an);
  T xx    = fn * (a0 - x) * invan;
  T yy    = fn * (a0 - y) * invan;
  T zz    = -(xx + yy) / 3;
  T xxyy  = xx * yy;
  T zz2   = sqr(zz);
  T e2    = fnma(T(6), zz2, xxyy);
  T e3    = (3 * xxyy - 8 * zz2) * zz;
  T e4    = 3 * (xxyy - zz2) * zz2;
  T e5    = xxyy * zz2 * zz;

  constexpr elt_t c0  = sizeof(elt_t) == 4 ? -3 / 14.0f : -3 / 14.0;
  constexpr elt_t c1  = sizeof(elt_t) == 4 ? 1 / 6.0f : 1 / 6.0;
  constexpr elt_t c2  = sizeof(elt_t) == 4 ? 9 / 88.0f : 9 / 88.0;
  constexpr elt_t c3  = sizeof(elt_t) == 4 ? -3 / 22.0f : -3 / 22.0;
  constexpr elt_t c4  = sizeof(elt_t) == 4 ? -9 / 52.0f : -9 / 52.0;
  constexpr elt_t c5  = sizeof(elt_t) == 4 ? 3 / 26.0f : 3 / 26.0;
  constexpr elt_t c6  = sizeof(elt_t) == 4 ? -1 / 16.0f : 1 / 16.0;
  constexpr elt_t c7  = sizeof(elt_t) == 4 ? 3 / 40.0f : 3 / 40.0;
  constexpr elt_t c8  = sizeof(elt_t) == 4 ? 3 / 20.0f : 3 / 20.0;
  constexpr elt_t c9  = sizeof(elt_t) == 4 ? 45 / 272.0f : 45 / 272.0;
  constexpr elt_t c10 = sizeof(elt_t) == 4 ? -9 / 68.0f : -9 / 68.0;

  T e22    = sqr(e2);
  T result = fn * invan * sqrt(invan)
             * (1 + e2 * c0 + e3 * c1 + e22 * c2 + e4 * c3 + e2 * (e3 * c4 + e22 * c6) + e5 * c5
                + sqr(e3) * c7 + e2 * e4 * c8 + c9 * e22 * e3 + (e3 * e4 + e2 * e5) * c10);

  return fma(T(3), rd_sum, result);
}

template<floating_real_value T>
EVE_FORCEINLINE T
ellint_rd_(EVE_SUPPORTS(cpu_), T x, T y, T z) noexcept requires has_native_abi_v<T>
{
  auto r       = nan(as(x));
  auto notdone = is_nltz(x) && is_nltz(y) && is_nlez(z) && is_nez(x + y);
  // z equal to zero or any parameter nan or less than zero or more than one of x and y zero implies
  // nan
  auto br0 = [x, y, z]() { return raw(ellint_rd)(x, y, z); };
  last_interval(br0, notdone, r);
  return r;
}
}
