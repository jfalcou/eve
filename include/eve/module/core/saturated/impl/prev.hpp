//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/converter.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/saturated/dec.hpp>
#include <eve/module/core/saturated/sub.hpp>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE constexpr auto
prev_(EVE_SUPPORTS(cpu_), saturated_type const&, T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( floating_value<T> )
    {
      auto z = if_else(a == minf(as(a)), a, prev(a));
      if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
      else return z;
    }
    else if constexpr( integral_value<T> ) { return saturated(dec)(a); }
  }
  else { return apply_over(saturated(prev), a); }
}

//////////////////////////////////////////////////////////////
// two parameters
//////////////////////////////////////////////////////////////
template<real_value T, integral_real_value U>
EVE_FORCEINLINE constexpr auto
prev_(EVE_SUPPORTS(cpu_), saturated_type const&, T const& a, U const& n) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( floating_value<T> )
    {
      auto z = if_else(a == minf(as(a)), a, prev(a, n));
      if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
      else return z;
    }
    else if constexpr( integral_value<T> ) { return saturated(sub)(a, to_<T>(n)); }
  }
  else { return apply_over(saturated(prev), a, n); }
}
}
