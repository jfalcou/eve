//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/detail/generic/rem180.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/cospi.hpp>
#include <eve/module/math/regular/div_180.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cosd_(EVE_SUPPORTS(cpu_), quarter_circle_type const&, T x) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return eve::quarter_circle(cospi)(div_180(x)); }
  else return apply_over(quarter_circle(cosd), x);
}

template<decorator D, floating_real_value T>
EVE_FORCEINLINE constexpr auto
cosd_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
    requires(is_one_of<D>(types<half_circle_type, full_circle_type, medium_type, big_type> {}))
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
      if( is_not_finite(a0) ) return nan(eve::as<T>());
    auto x             = eve::abs(a0);
    auto [fn, xr, dxr] = rem180(x);
    return cos_finalize(fn, xr, dxr);
  }
  else return apply_over(D()(cosd), a0);
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cosd_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x = abs(a0);
    if( eve::all(eve::abs(x) <= T(45)) ) return quarter_circle(cosd)(x);
    else return big(cosd)(x);
  }
  else return apply_over(cosd, a0);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
cosd_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::cosd, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
cosd_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::cosd), t);
}
}
