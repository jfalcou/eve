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
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> logical_not_(EVE_REQUIRES(avx512_), O const&, logical<wide<T, N>> v) noexcept
    requires (x86_abi<abi_t<T, N>>)
  {
    using l_t = logical<wide<T, N>>;
    return l_t {~v.storage()};
  }
}
