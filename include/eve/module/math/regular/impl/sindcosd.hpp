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
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/regular/sinpicospi.hpp>

#include <type_traits>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE constexpr auto
sindcosd_(EVE_SUPPORTS(cpu_), quarter_circle_type const&, T x) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return eve::quarter_circle(sinpicospi)(div_180(x)); }
  else return apply_over2(quarter_circle(sindcosd), x);
}

template<decorator D, floating_ordered_value T>
EVE_FORCEINLINE constexpr kumi::tuple<T, T>
sindcosd_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
    requires(is_one_of<D>(types<half_circle_type, full_circle_type, medium_type, big_type> {}))
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
      if( is_not_finite(a0) ) return {nan(eve::as<T>()), nan(eve::as<T>())};
    auto x             = eve::abs(a0);
    x                  = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
    auto [fn, xr, dxr] = rem180(x);
    return sincos_finalize(bitofsign(a0), fn, xr, dxr);
  }
  else return apply_over2(D()(sindcosd), a0);
}

template<floating_ordered_value T>
EVE_FORCEINLINE constexpr auto
sindcosd_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x = abs(a0);
    if( eve::all(eve::abs(x) <= T(45)) ) return quarter_circle(sindcosd)(a0);
    else return big(sindcosd)(a0);
  }
  else return apply_over2(sindcosd, a0);
}

}
