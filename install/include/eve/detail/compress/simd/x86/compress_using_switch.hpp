//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{

  template<relative_conditional_expr C, typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_using_switch_(EVE_SUPPORTS(sse2_),
                                 C c,
                                 wide<T, N> v,
                                 logical<wide<U, N>> mask) noexcept
    requires (sizeof(U) == 2)
  {
    // make 1 bit top bits
    return compress_using_switch(c, v, convert(mask, as<logical<std::uint8_t>>{}));
  }
}
