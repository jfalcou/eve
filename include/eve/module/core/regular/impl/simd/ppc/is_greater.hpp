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
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> is_greater_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(definitely)) return is_greater.behavior(cpu_{}, opts, a, b);
    else                                   return logical<wide<T, N>>(vec_cmpgt(a.storage(), b.storage()));
  }
}
