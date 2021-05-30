//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_real_value T, typename N>
  EVE_FORCEINLINE wide<T, N> nearest_(EVE_SUPPORTS(vmx_), wide<T, N> const &v0) noexcept
      requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(std::is_same_v<T, float>) { return vec_round(v0.storage()); }
    else if constexpr(std::is_same_v<T, double>)
    {
      // TODO(joel) : Test on proper VSX HW
      return map(eve::nearest, v0);
    }
  }
}
