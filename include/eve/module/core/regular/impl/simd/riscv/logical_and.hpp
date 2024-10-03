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
  EVE_FORCEINLINE logical<wide<T, N>> logical_and_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> a, logical<wide<U, N>> b) noexcept
    requires(rvv_abi<abi_t<T, N>> || rvv_abi<abi_t<U, N>>)
  {
    return __riscv_vmand(a, bit_cast(b, as<logical<wide<T, N>>>{}), N::value);
  }
}
