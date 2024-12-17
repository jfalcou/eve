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
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto logical_or_(EVE_REQUIRES(avx512_), O const&, logical<wide<T, N>> a, logical<wide<T, N>> b) noexcept
    requires (x86_abi<abi_t<T, N>>)
  {
    return logical<wide<T, N>>{a.storage() | b.storage()};
  }
}
