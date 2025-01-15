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
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> logical_or_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> a, logical<wide<T, N>> b) noexcept
    requires (rvv_abi<abi_t<T, N>>)
  {
    return __riscv_vmor(a, b, N::value);
  }
}
