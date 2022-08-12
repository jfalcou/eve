//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/sincos.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr kumi::tuple<T, T>
sinpicospi_(EVE_SUPPORTS(cpu_), quarter_circle_type const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return quarter_circle(sincos)(a0 * pi(eve::as<T>())); }
  else return apply_over2(quarter_circle(sinpicospi), a0);
}

template<decorator D, floating_real_value T>
EVE_FORCEINLINE constexpr kumi::tuple<T, T>
sinpicospi_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
    {
      if( is_not_finite(a0) ) return {nan(eve::as<T>()), nan(eve::as<T>())};
    }
    T x = abs(a0);
    if constexpr( scalar_value<T> )
    {
      if( x > maxflint(eve::as<T>()) ) return {T {0}, T(1)};
    }
    else
    {
      auto invalid = is_not_finite(x);
      x            = if_else(x > maxflint(eve::as(x)), eve::zero, x);
      x            = if_else(invalid, eve::allbits, x);
    }
    auto [fn, xr, dxr] = rem2(x);
    auto [s, c]        = sincos_finalize(bitofsign(a0), fn, xr, dxr);
    return {s, c};
  }
  else return apply_over2(D()(sinpicospi), a0);
}

template<typename T>
EVE_FORCEINLINE constexpr kumi::tuple<T, T>
sinpicospi_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x = abs(a0);
    if( eve::all(x <= T(0.25)) ) return quarter_circle(sinpicospi)(a0);
    else return big(sinpicospi)(a0);
  }
  else return apply_over2(sinpicospi, a0);
}
}
