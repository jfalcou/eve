//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/csc.hpp>
#include <eve/module/math/regular/sin.hpp>

#include <type_traits>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE constexpr auto
cscpi_(EVE_SUPPORTS(cpu_), quarter_circle_type const&, T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return quarter_circle(csc)(a0 * pi(eve::as<T>())); }
  else return apply_over(quarter_circle(cscpi), a0);
}

template<decorator D, floating_ordered_value T>
EVE_FORCEINLINE constexpr auto
cscpi_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
    {
      if( is_eqz(a0) ) return rec(a0);
      if( is_flint(a0) || is_not_finite(a0) ) return nan(eve::as<T>()); // nan or Inf input
    }
    T x = abs(a0);
    if constexpr( simd_value<T> )
    {
      x = if_else(is_nez(a0) && (is_not_finite(x) || is_flint(x)), eve::allbits, x);
    }
    auto [fn, xr, dxr] = rem2(x);
    return rec(sin_finalize(bitofsign(a0), quadrant(fn), xr, dxr));
  }
  else return apply_over(D()(cscpi), a0);
}

template<floating_ordered_value T>
EVE_FORCEINLINE constexpr auto
cscpi_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if( eve::all(eve::abs(a0) <= T(0.25)) ) return quarter_circle(cscpi)(a0);
    else return big(cscpi)(a0);
  }
  else return apply_over(cscpi, a0);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
cscpi_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::cscpi, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
cscpi_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::cscpi), t);
}
}
