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
  EVE_FORCEINLINE wide<T, N> bit_not_(EVE_REQUIRES(vmx_), O const&, wide<T, N> w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return vec_nor(w.storage(), w.storage());
  }
}
