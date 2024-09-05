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
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_and_(EVE_REQUIRES(vmx_), O const&, wide<T, N> a, wide<T, N> b) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return vec_and(a.storage(), b.storage());
  }
}
