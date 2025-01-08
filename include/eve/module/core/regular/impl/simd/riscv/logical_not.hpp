//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  #warning test
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> logical_not_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> v) noexcept
    requires rvv_abi<abi_t<T, N>>
  {
    return __riscv_vmnot(v, N::value);
  }
}
