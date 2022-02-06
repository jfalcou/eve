//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> div_(EVE_SUPPORTS(neon128_)
                                      , wide<T, N> v0
                                      , wide<T, N> const &v1) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return v0 /= v1;
  }
}
