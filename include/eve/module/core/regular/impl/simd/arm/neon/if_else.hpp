//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve::detail
{
  template<typename T, typename N, callable_options O>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_REQUIRES(neon128_), O, logical<wide<T,N>> m, logical<wide<T,N>> v0, logical<wide<T,N>> v1) noexcept
  requires arm_abi<abi_t<T,N>>
  {
    return bit_cast(if_else(m, v0.mask(), v1.mask()), as{v0});
  }
}
