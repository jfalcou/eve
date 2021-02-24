//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> max_(EVE_SUPPORTS(vmx_)
                                       , wide<T, N, ppc_> const &v0
                                       , wide<T, N, ppc_> const &v1) noexcept
  {
    return vec_max(v0.storage(), v1.storage());
  }
}

