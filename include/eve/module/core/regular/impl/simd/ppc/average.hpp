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
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve::detail
{
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                average_(EVE_SUPPORTS(vmx_),
                         wide<T, N> const                &v0,
                         wide<T, N> const                &v1) noexcept requires ppc_abi<abi_t<T, N>>
{
  if constexpr( integral_value<T> && sizeof(T) < 8 ) return vec_avg(v0.storage(), v1.storage());
  else if constexpr( floating_value<T> ) return fma(v0, half(eve::as(v0)), v1 * half(eve::as(v0)));
  else return map(average, v0, v1);
}
}
