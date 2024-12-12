//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename U, typename N>
  EVE_FORCEINLINE auto logical_or_(EVE_REQUIRES(sse2_), O const& opts, logical<wide<T, N>> a, logical<wide<U, N>> b) noexcept
    requires (x86_abi<abi_t<T, N>> || x86_abi<abi_t<U, N>>)
  {
    if constexpr (use_is_wide_logical<abi_t<T, N>>::value)
    {
      return logical_or.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      typename common_logical_t<wide<T, N>, wide<U, N>>::storage_type dst;
      dst.value = a.storage().value | b.storage().value;
      return dst;
    }
  }
}
