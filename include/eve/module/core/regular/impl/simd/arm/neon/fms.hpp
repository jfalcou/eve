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
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  fms_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> const& a, wide<T, N> const& b, wide<T, N> const& c) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    return fma[o](a, b, -c);

  }
}
