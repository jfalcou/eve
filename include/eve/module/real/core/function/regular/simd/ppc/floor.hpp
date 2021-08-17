//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> floor_(EVE_SUPPORTS(vmx_), wide<T, N> const &v0) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(floating_value<T>) return vec_floor(v0.storage());
    else                            return v0;
  }
}
