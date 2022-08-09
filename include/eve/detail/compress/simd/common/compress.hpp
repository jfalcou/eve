//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/compress/compress_using_masks.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_(EVE_SUPPORTS(cpu_), C c, wide<T, N> v, logical<wide<U, N>> mask) noexcept
  {
    return compress_using_masks[c](v, mask);
  }
}
