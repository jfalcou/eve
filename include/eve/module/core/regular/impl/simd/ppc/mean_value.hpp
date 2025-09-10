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
  EVE_FORCEINLINE wide<T, N> mean_value_(EVE_REQUIRES(vmx_),
                                      O          const &opts,
                                      wide<T, N> const &v0,
                                      wide<T, N> const &v1) noexcept requires ppc_abi<abi_t<T, N>>
  {
    if constexpr( integral_value<T> && sizeof(T) < 8 )
      return vec_avg(v0.storage(), v1.storage());
    else if constexpr( O::contains(upper) && integral_value<T>)
      return mean_value.behavior(cpu_{}, opts, v0, v1);
    else if constexpr( floating_value<T> )
      return fma[opts](v0, half(eve::as(v0)), v1 * half(eve::as(v0)));
    else
      return map(mean_value[opts], v0, v1);
  }
}
