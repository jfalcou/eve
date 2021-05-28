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
  template<real_scalar_value U, typename N>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(neon128_)
                                , logical<wide<U, N>> const &v0
                                , logical<wide<U, N>> const &v1
                                , logical<wide<U, N>> const &v2
                                ) noexcept
      requires arm_abi<abi_t<U, N>>
  {
    return bit_cast(if_else(v0, v1.mask(), v2.mask()), as(v0));
  }
}
