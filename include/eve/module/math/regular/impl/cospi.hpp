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
#include <eve/module/math/regular/cos.hpp>

#include <type_traits>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cospi_(EVE_SUPPORTS(cpu_), quarter_circle_type const&, T x) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return eve::quarter_circle(cos)(x * pi(eve::as<T>())); }
  else return apply_over(quarter_circle(cospi), x);
}

template<decorator D, floating_real_value T>
EVE_FORCEINLINE constexpr auto
cospi_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
    requires(is_one_of<D>(types<half_circle_type, full_circle_type, medium_type, big_type> {}))
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
      if( is_not_finite(a0) ) return nan(eve::as<T>());
    auto x = eve::abs(a0);
    if constexpr( scalar_value<T> )
    {
      if( x > maxflint(eve::as<T>()) ) return T(1);
    }
    else
    {
      x = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
      x = if_else(is_greater(x, maxflint(eve::as(x))), eve::zero, x);
    }
    auto [fn, xr, dxr] = rem2(x);
    return cos_finalize(fn, xr, dxr);
  }
  else return apply_over(D()(cospi), a0);
}

template<decorator D, signed_integral_value T>
EVE_FORCEINLINE constexpr auto
cospi_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
    return if_else(is_odd(a0), eve::mone, one(eve::as(a0))); //(-1)^n
  else return apply_over(D()(cospi), a0);
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cospi_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x = abs(a0);
    if( eve::all(eve::abs(x) <= T(0.25)) ) return quarter_circle(cospi)(x);
    else return big(cospi)(x);
  }
  else return apply_over(cospi, a0);
}

template<signed_integral_value T>
EVE_FORCEINLINE constexpr auto
cospi_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
    return if_else(is_odd(a0), eve::mone, one(eve::as(a0))); //(-1)^n
  else return apply_over(cospi, a0);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
cospi_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::cospi, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
cospi_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::cospi), t);
}
}
