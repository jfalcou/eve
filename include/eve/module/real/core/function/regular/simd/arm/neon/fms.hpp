//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/fma.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> fms_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, ABI> const &v0,
                                           wide<T, N, ABI> const &v1,
                                           wide<T, N, ABI> const &v2) noexcept
  {
    return fma(v0, v1, -v2);
  }
}
