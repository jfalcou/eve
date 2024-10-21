//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve::detail
{
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> average_(EVE_SUPPORTS(vmx_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr( integral_value<T> && sizeof(T) < 8 )
      return vec_avg(a.storage(), b.storage());
    else if constexpr( O::contains(upper) && integral_value<T>)
      return average.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    else if constexpr( floating_value<T> )
      return fma[opts](a, half(eve::as{a}), b * half(eve::as{a}));
    else
      return map(as<wide<T, N>>{}, average[opts], a, b);
  }
}
