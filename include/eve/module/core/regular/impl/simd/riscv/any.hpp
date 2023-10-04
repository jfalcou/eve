//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<scalar_value T, typename N, relative_conditional_expr C>
EVE_FORCEINLINE bool
any_(EVE_SUPPORTS(rvv_), C const& cond, logical<wide<T, N>> v) noexcept
requires rvv_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete && !C::is_inverted ) return false;
  else
  {
    auto m = expand_mask(cond, as<wide<T, N>> {});
    return __riscv_vcpop(m, v, N::value) > 0;
  }
}
}
