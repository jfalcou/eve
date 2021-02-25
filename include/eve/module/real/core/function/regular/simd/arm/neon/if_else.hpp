//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>

namespace eve::detail
{
  //================================================================================================
  // Full logical if_else
  template<real_scalar_value U, typename N, arm_abi ABI>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(neon128_)
                                , logical<wide<U, N, ABI>> const &v0
                                , logical<wide<U, N, ABI>> const &v1
                                , logical<wide<U, N, ABI>> const &v2
                                ) noexcept
  {
    return bit_cast(if_else(v0, v1.mask(), v2.mask()), as(v0));
  }
}
