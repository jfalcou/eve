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
  EVE_FORCEINLINE logical<wide<T, N>> logical_and_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> v, logical<wide<U, N>> w) noexcept
    requires(rvv_abi<abi_t<T, N>> || rvv_abi<abi_t<U, N>>)
  {
    return __riscv_vmand(v, bit_cast(w, as<logical<T>>{}), N::value);
  }
}
