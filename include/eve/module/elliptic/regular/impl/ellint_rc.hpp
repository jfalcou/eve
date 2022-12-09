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
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
template<floating_ordered_value T, floating_ordered_value U>
EVE_FORCEINLINE auto
ellint_rc_(EVE_SUPPORTS(cpu_), T x, U y) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(ellint_rc, x, y);
}

template<floating_ordered_value T>
EVE_FORCEINLINE T
ellint_rc_(EVE_SUPPORTS(cpu_), T x, T y) noexcept requires has_native_abi_v<T>
{
  auto ylt0   = is_ltz(y);
  auto prefix = one(as(x));
  if( eve::any(ylt0) ) // provisions for y < 0
  {
    prefix = if_else(ylt0, sqrt(x / (x - y)), one);
    x      = sub[ylt0](x, y);
    y      = if_else(ylt0, -y, y);
  }
  // now all y are >= 0
  auto r       = nan(as(x));
  auto notdone = is_nltz(x) && is_nez(y);
  if( eve::any(notdone) )
  {
    auto tmp0 = rsqrt(y);
    auto br_0 = [tmp0](auto x, auto y) // x == y || x == 0
    {
      auto z = mul[is_eqz(x)](tmp0, pio_2(as(y)));
      return z; // if_else(x == y, tmp0, tmp0*pio_2(as(y)));
    };
    notdone = next_interval(br_0, notdone, (x == y) || is_eqz(x), r, x, y);
    if( eve::any(notdone) )
    {
      auto tmp1 = sqrt(eve::abs(x - y));
      auto tmp2 = rsqrt(x);
      auto tmp3 = tmp1 * tmp2;
      auto br_1 = [tmp1, tmp3]() // y >  x
      { return atan(tmp3) / tmp1; };
      notdone = next_interval(br_1, notdone, y > x, r);
      if( eve::any(notdone) )
      {
        auto br_2 = [tmp1, tmp3]() // y > 0.5*x
        { return atanh(tmp3) / tmp1; };
        notdone = next_interval(br_2, notdone, y > T(0.5) * x, r);
        if( eve::any(notdone) )
        {
          auto br_3 = [tmp0, tmp1](auto x) { return log((sqrt(x) + tmp1) * tmp0) / tmp1; };
          last_interval(br_3, notdone, r, x);
        }
      }
    }
  }
  return if_else(x == inf(as(x)), zero, r * prefix);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename T0, typename ... Ts>
EVE_FORCEINLINE auto
ellint_rc_(EVE_SUPPORTS(cpu_), C const& cond, T0 t0, Ts ... ts) noexcept
-> decltype( if_else(cond, ellint_rc(t0, ts...), t0) )
{
  return mask_op(cond, eve::ellint_rc, t0, ts ...);
}

template<conditional_expr C, decorator D, typename T0, typename  ... Ts>
EVE_FORCEINLINE auto
ellint_rc_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, T0 t0, Ts ... ts) noexcept
-> decltype( if_else(cond, ellint_rc(t0, ts...), t0) )
{
  return mask_op(cond, d(eve::ellint_rc), t0, ts ...);
}
}
