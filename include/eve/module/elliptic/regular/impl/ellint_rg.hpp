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
#include <eve/module/elliptic/regular/ellint_rf.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
template<floating_ordered_value T, floating_ordered_value U, floating_ordered_value V>
EVE_FORCEINLINE auto
ellint_rg_(EVE_SUPPORTS(cpu_),
           T x,
           U y,
           V z) noexcept
-> common_value_t<T, U, V>
{
  return arithmetic_call(ellint_rg, x, y, z);
}

template<floating_ordered_value T, floating_ordered_value U, floating_ordered_value V>
EVE_FORCEINLINE auto
ellint_rg_(EVE_SUPPORTS(cpu_), raw_type const&, T x, U y, V z) noexcept
-> common_value_t<T, U, V>
{
  return arithmetic_call(raw(ellint_rg), x, y, z);
}

template<floating_ordered_value T>
EVE_FORCEINLINE T
ellint_rg_(EVE_SUPPORTS(cpu_), raw_type const&, T x, T y, T z) noexcept requires has_native_abi_v<T>
{
  auto cond_swap = [](auto cond, auto& a, auto& b)
  {
    auto aa = if_else(cond, a, b);
    auto bb = if_else(cond, b, a);
    a       = aa;
    b       = bb;
  };
  cond_swap(x < y, x, y);
  cond_swap(x < z, x, z);
  cond_swap(y > z, y, z);
  // now all(x >= z) and all(z >= y)
  return (z * ellint_rf(x, y, z) - (x - z) * (y - z) * ellint_rd(x, y, z) / 3 + sqrt(x * y / z))
         * half(as(x));
}

template<floating_ordered_value T>
EVE_FORCEINLINE T
ellint_rg_(EVE_SUPPORTS(cpu_), T x, T y, T z) noexcept requires has_native_abi_v<T>
{
  auto r       = nan(as(x));
  auto notdone = is_nltz(x) && is_nltz(y) && is_nltz(z);
  // any parameter nan or less than zero implies nan
  auto br0 = [x, y, z]() { return raw(ellint_rg)(x, y, z); };
  last_interval(br0, notdone, r);
  return r;
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename T0, typename ... Ts>
EVE_FORCEINLINE auto
ellint_rg_(EVE_SUPPORTS(cpu_), C const& cond, T0  t0, Ts ... ts) noexcept
-> decltype( if_else(cond, ellint_rg(t0, ts...), t0) )
{
  return mask_op(cond, eve::ellint_rg, t0, ts ...);
}

template<conditional_expr C, decorator D, typename T0, typename  ... Ts>
EVE_FORCEINLINE auto
ellint_rg_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, T0 t0, Ts ... ts) noexcept
-> decltype( if_else(cond, ellint_rg(t0, ts...), t0) )
{
  return mask_op(cond, d(eve::ellint_rg), t0, ts ...);
}
}
